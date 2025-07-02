#include "WinsockHelper.h"

#include <iostream>

#include "RemoteManagement.h"
#include "server.h"

using std::cout;
using std::endl;
using std::string;

PCSTR PORT = "12345";

LSTATUS createProgramMutex() {
    HANDLE programMutex = CreateMutexA(NULL, TRUE, "RemoteManagementMutex");
    if (programMutex == NULL) {
        LSTATUS lastError = GetLastError();
        if (lastError != ERROR_SUCCESS) {
            cout << "A Remote Management process is already running" << endl;
            return lastError;
        }
    }
    return ERROR_SUCCESS;
}

LSTATUS addPathToRegistry(HKEY keyHandle, const string programPath) {
    DWORD pathSize = static_cast<DWORD>(programPath.size()) + 1;
    const BYTE* path = reinterpret_cast<const BYTE*>(programPath.c_str());

    LSTATUS status = RegSetValueExA(keyHandle, VALUE_NAME, 0, REG_SZ, path, pathSize);
    if (status != ERROR_SUCCESS) {
        cout << "Couldn't set registry key value: Error " << status;
        return status;
    }
    return ERROR_SUCCESS;
}

void runRemoteManagementProgram() {
    MessageBoxA(NULL, MESSAGE_BOX_TEXT, MESSAGE_BOX_TITLE, MESSAGE_BOX_TYPE);
    startServer();
}