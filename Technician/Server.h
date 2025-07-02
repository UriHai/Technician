#pragma once

#include <winsock2.h>

// Create socket, accpet connections and handle them
int startServer(void);

// Handle client connection
int handleConnection(SOCKET clientSocket);