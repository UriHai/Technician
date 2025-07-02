#pragma once

#include "windows.h"

#include <string>


const std::string VALUE_NAME = "RemoteManagement";

const std::string MESSAGE_BOX_TITLE = "Remote Managment";
const std::string MESSAGE_BOX_TEXT = "Managment program is up";
constexpr UINT MESSAGE_BOX_TYPE = MB_OK | MB_ICONINFORMATION;

constexpr size_t MILLISECONDS_IN_SECOND = 1000;
constexpr size_t SECONDS_IN_MINUTE = 60;
constexpr size_t MINUTES_IN_HOUR = 60;
constexpr size_t MILLISECONDS_IN_HOUR = MILLISECONDS_IN_SECOND * SECONDS_IN_MINUTE * MINUTES_IN_HOUR;
constexpr DWORD SLEEP_TIME = static_cast<DWORD>(MILLISECONDS_IN_HOUR);

/**
 * @brief Add the path as a registry value
 *
 * @param keyHandle   [IN] Handle to the registry run key
 * @param programPath [IN] The path to the program's exe file 
 * 
 * @return Error status
 */
LSTATUS addPathToRegistry(HKEY keyHandle, const std::string programPath);

// Run the program
void runRemoteManagementProgram();