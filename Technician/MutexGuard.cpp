#include "MutexGuard.h"

#include <windows.h>
#include <iostream>

using std::cout;
using std::endl;

MutexGuard::MutexGuard(LPCSTR name) {
    m_mutexHandle = CreateMutexA(NULL, TRUE, name);
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