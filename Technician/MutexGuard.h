#pragma once

#include <windows.h>

class MutexGuard {
public:
    /**
     * @brief MutexGuard constructor
     * 
     * @param name [IN] Mutex name
     */
    MutexGuard(LPCSTR name);

    // MutexGuard deconstructor
    ~MutexGuard();

private:
    HANDLE m_mutexHandle;
};