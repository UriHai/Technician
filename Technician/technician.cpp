#include "windows.h"
#include <string>

#define RUN_KEY_PATH ("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run")
#define KEY_NAME ("RemoteManagment")
#define MESSAGE_BOX_TITLE ("Remote Managment")
#define MESSAGE_BOX_TEXT ("Managment program is up")

#define MILLISECONDS_IN_SECOND (100)
#define SECONDS_IN_MINUTE (60)
#define MINUTES_IN_HOUR (60)
#define MILLISECONDS_IN_HOUR (MILLISECONDS_IN_SECOND * SECONDS_IN_MINUTE * MINUTES_IN_HOUR)
#define SLEEP_TIME (MILLISECONDS_IN_HOUR)

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
		status = RegCloseKey(keyHandle);
	} else {
		status = RegCloseKey(keyHandle);
		MessageBoxA(NULL, MESSAGE_BOX_TEXT, MESSAGE_BOX_TITLE, MB_OK | MB_ICONINFORMATION);
		Sleep(SLEEP_TIME);
	}

	return 0;
}