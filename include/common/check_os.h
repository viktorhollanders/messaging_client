#ifndef CHECK_OS_H
#define CHECK_OS_H

#ifdef _WIN32
    #define MY_OS "Windows"
    #include <Winsocket.h>
    using socket_t = SOCKET;
    using address_size_t = int;
    using socklen_t = int;
    #define ON_WINDOWS
    #define SOCKET_ERROR_VALUE INVALID_SOCKET
    #define GET_SOCKET_ERROR WSAGetLastError()
#else
    using socket_t = int;
    using address_size_t = unsigned int;
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #define SOCKET_ERROR_VALUE (-1)
    #define GET_SOCKET_ERROR errno
#endif

bool check_os();

#endif
