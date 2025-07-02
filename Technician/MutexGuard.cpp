#include "MutexGuard.h"

#include <windows.h>
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

MutexGuard::MutexGuard(string name) {
    m_mutexHandle = CreateMutexA(NULL, TRUE, static_cast<LPCSTR>(name.c_str()));
    LSTATUS lastError = GetLastError();
    if (m_mutexHandle == NULL) {
        cout << "CreateMutexA failed. Error: " << lastError;
        throw lastError;
    } else if (lastError != ERROR_ALREADY_EXISTS) {
        throw lastError;
        cout << "A Remote Management process is already running" << endl;
    }
}

MutexGuard::~MutexGuard() {
    ReleaseMutex(m_mutexHandle);
}