#include "windows.h"
#include <string>
#include <iostream>
#include <mutex>

#include "RemoteManagement.h"

using std::string;
using std::cout;
using std::endl;
using std::mutex;
using std::lock_guard;

int main(int nargs, char* args[]) {
	HANDLE programMutex = CreateMutexA(NULL, TRUE, "RemoteManagementMutex");
	DWORD lastError = GetLastError();
	if (lastError != ERROR_SUCCESS) {
		cout << "A Remote Management process is already running" << endl;
		return lastError;
	}

	const string programPath = args[0];
	HKEY keyHandle = 0;
	PHKEY pKeyHandle = &keyHandle;
	LPBYTE keyValue = { 0 };

	LSTATUS status = RegOpenKeyA(HKEY_LOCAL_MACHINE, RUN_KEY_PATH, pKeyHandle);
	if (status != ERROR_SUCCESS) {
		cout << "Couldn't open Run registry key: Error " << status << endl;
		return status;
	}

	status = RegQueryValueExA(keyHandle, VALUE_NAME, 0, NULL, NULL, NULL);
	if (status == ERROR_SUCCESS) {
		runRemoteManagementProgram();
	} else if (status == ERROR_FILE_NOT_FOUND) {
		status = addPathToRegistry(keyHandle, programPath);
		return status;
	} else {
		cout << "Failed to query for registy value: Error " << status << endl;
	}

	status = RegCloseKey(keyHandle);
	if (status != ERROR_SUCCESS) {
		cout << "Couldn't close Run registry key: Error " << status << endl;
		return status;
	}

	return 0;
}