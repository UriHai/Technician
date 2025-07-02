#include "RegKeyGuard.h"

#include <windows.h>
#include <iostream>

using std::cout;
using std::endl;

RegKeyGuard::RegKeyGuard(HKEY hKey, std::string keyPath, PHKEY pKeyHandle) {
	LSTATUS status = RegOpenKeyA(HKEY_LOCAL_MACHINE, static_cast<LPCSTR>(keyPath.c_str()), pKeyHandle);
	if (status != ERROR_SUCCESS) {
		cout << "Couldn't open Run registry key: Error " << status << endl;
		throw status;
	}
	m_regKeyHandle = *pKeyHandle;
}

RegKeyGuard::~RegKeyGuard() {
    LSTATUS status = RegCloseKey(m_regKeyHandle);
    if (status != ERROR_SUCCESS) {
        cout << "Couldn't close registry key: Error " << status << endl;
    }
}