#pragma once

#include <windows.h>
#include <string>

class MutexGuard final {
public:
    /**
     * @brief MutexGuard constructor
     * 
     * @param name [IN] Mutex name
     */
    MutexGuard(std::string name);

    // MutexGuard deconstructor
    ~MutexGuard();

private:
    HANDLE m_mutexHandle;
};