#pragma once

#include <windows.h>
#include <string>

class RegKeyGuard {
public:
    /**
     * @brief RegKeyGuard constructor
     *
     * @param name [IN] Mutex name
     */
    RegKeyGuard(HKEY hKey, std::string keyPath, PHKEY pKeyHandle);

    // RegKeyGuard deconstructor
    ~RegKeyGuard();

private:
    HANDLE m_mutexHandle;
};