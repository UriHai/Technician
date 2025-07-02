#include "windows.h"
#include <string>
#include <iostream>

#include "RemoteManagement.h"
#include "MutexGuard.h"
#include "RegKeyGuard.h"

using std::string;
using std::cout;
using std::endl;

const string MUTEX_NAME = "RemoteManagementMutex";
const string RUN_KEY_PATH = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";

int innerMain(int nargs, char* args[]) {
	// Create program mutex to make sure there is no other process running
	MutexGuard programMutex(MUTEX_NAME);

	// Get registry key handle
	const string programPath = args[0];
	HKEY keyHandle = 0;
	PHKEY pKeyHandle = &keyHandle;
	LPBYTE keyValue = { 0 };
	RegKeyGuard regKeyGuard(HKEY_LOCAL_MACHINE, RUN_KEY_PATH, pKeyHandle);
	
	// Check if 
	LSTATUS status = RegQueryValueExA(keyHandle, static_cast<LPCSTR>(VALUE_NAME.c_str()), 0, NULL, NULL, NULL);
	if (status == ERROR_SUCCESS) {
		runRemoteManagementProgram();
	}
	else if (status == ERROR_FILE_NOT_FOUND) {
		status = addPathToRegistry(keyHandle, programPath);
		return status;
	}
	else {
		cout << "Failed to query for registy value: Error " << status << endl;
	}

	return 0;
}

int main(int nargs, char* args[]) {
	try {
		innerMain(nargs, args);
	} catch (int status) {
		return status;
	}

	return 0;
}

