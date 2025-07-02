#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include "Server.h"

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

using std::cout;
using std::endl;

const PCSTR DEFAULT_PORT = "12345";
const int BUFFER_LENGTH = 512;

int startServer(void)
{
    int status = ERROR;

    // Initialize Winsock
    WSADATA wsaData = { 0 };
    status = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (status != 0) {
        cout << "WSAStartup failed with error: " << status << endl;
        return 1;
    }

    // Resolve the server address and port
    struct addrinfo* addressInformation = NULL;
    struct addrinfo hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    status = getaddrinfo(NULL, DEFAULT_PORT, &hints, &addressInformation);
    if (status != 0) {
        cout << "getaddrinfo failed: " << status << endl;
        WSACleanup();
        return 1;
    }

    // Create a socket for the server 
    SOCKET listenSocket = socket(addressInformation->ai_family, addressInformation->ai_socktype, addressInformation->ai_protocol);
    if (listenSocket == INVALID_SOCKET) {
        cout << "socket failed with error: " << WSAGetLastError() << endl;
        freeaddrinfo(addressInformation);
        WSACleanup();
        return 1;
    }

    // Bind the socket
    status = bind(listenSocket, addressInformation->ai_addr, (int)addressInformation->ai_addrlen);
    if (status == SOCKET_ERROR) {
        cout << "bind failed with error: " << WSAGetLastError() << endl;
        freeaddrinfo(addressInformation);
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    freeaddrinfo(addressInformation);

    // Listen on socket
    status = listen(listenSocket, SOMAXCONN);
    if (status == SOCKET_ERROR) {
        cout << "listen failed with error: " << WSAGetLastError() << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    SOCKET clientSocket = accept(listenSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        cout << "accept failed with error: " << WSAGetLastError() << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    closesocket(listenSocket);

    handleConnection(clientSocket);

    // Close the connection
    status = shutdown(clientSocket, SD_SEND);
    if (status == SOCKET_ERROR) {
        cout << "shutdown failed with error: " << WSAGetLastError() << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    // Cleanup
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}

int handleConnection(SOCKET clientSocket) {
    // Receive until the peer shuts down the connection
    int status = 0;
    char recvbuf[BUFFER_LENGTH] = { 0 };
    int recvbuflen = BUFFER_LENGTH;
    do {
        status = recv(clientSocket, recvbuf, recvbuflen, 0);
        if (status > 0) {
            cout << "Bytes received: " << status << endl;

            // Echo the buffer back to the sender
            status = send(clientSocket, recvbuf, status, 0);
            if (status == SOCKET_ERROR) {
                cout << "send failed with error : " << WSAGetLastError() << endl;
                closesocket(clientSocket);
                WSACleanup();
                return 1;
            }
            cout << "Bytes sent: " << status << endl;
        }
        else if (status == 0)
            cout << "Connection closing..." << endl;
        else {
            cout << "recv failed with error: " << WSAGetLastError() << endl;
            closesocket(clientSocket);
            WSACleanup();
            return 1;
        }
    } while (status > 0);
}