#include "RemoteManagement.h"

#include <iostream>
#include <mutex>

#include "windows.h"

using std::cout;
using std::endl;
using std::string;

LSTATUS addPathToRegistry(HKEY keyHandle, const string programPath) {
    DWORD pathSize = static_cast<DWORD>(programPath.size()) + 1;
    const BYTE* path = reinterpret_cast<const BYTE*>(programPath.c_str());

    LSTATUS status = RegSetValueExA(keyHandle, static_cast<LPCSTR>(VALUE_NAME.c_str()), 0, REG_SZ, path, pathSize);
    if (status != ERROR_SUCCESS) {
        cout << "Couldn't set registry key value: Error " << status;
        return status;
    }
    return ERROR_SUCCESS;
}

void runRemoteManagementProgram() {
    MessageBoxA(NULL, static_cast<LPCSTR>(MESSAGE_BOX_TEXT.c_str()), static_cast<LPCSTR>(MESSAGE_BOX_TITLE.c_str()), MESSAGE_BOX_TYPE);
    Sleep(SLEEP_TIME);
}