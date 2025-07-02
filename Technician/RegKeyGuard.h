#pragma once

#include <windows.h>
#include <string>

class RegKeyGuard final {
public:
    /**
     * @brief RegKeyGuard constructor
     *
     * @param hKey       [IN]  Handle to the registry key
     * @param keyPath    [IN]  Registry key path
     * @param pKeyHandle [OUT] Pointer to the key handle
     */
    RegKeyGuard(HKEY hKey, std::string keyPath, PHKEY pKeyHandle);

    // RegKeyGuard deconstructor
    ~RegKeyGuard();

private:
    HKEY m_regKeyHandle;
};