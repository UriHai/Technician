#pragma once

#include "WinsockHelper.h"

// Create socket, accpet connections and handle them
int startServer(void);

// Handle client connection
int handleConnection(SOCKET clientSocket);