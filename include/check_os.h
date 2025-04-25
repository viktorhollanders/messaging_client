#ifndef CHECK_OS_H
#define CHECK_OS_H

// Common includes needed everywhere
#include <stdexcept>
#include <string>
#include <iostream>

#ifdef _WIN32
    #define MY_OS "Windows"
    #include <winsock2.h>
    #include <ws2tcpip.h>

    using socket_t = SOCKET;
    using socket_address_t = struct sockaddr;
    using socket_address_in_t = struct sockaddr_in;
    using address_size_t = int;

    #define ON_WINDOWS
    #define SOCKET_ERROR_VALUE INVALID_SOCKET
    #define GET_SOCKET_ERROR WSAGetLastError()
#else
    #define MY_OS "Unix/Linux"


    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <errno.h>

    using socket_t = int;
    using socket_address_t = struct sockaddr;
    using socket_address_in_t = struct sockaddr_in;
    using address_size_t = unsigned int;

    #define SOCKET_ERROR_VALUE (-1)
    #define GET_SOCKET_ERROR errno
#endif

bool check_os();

void cleanup_sockets();
#endif
