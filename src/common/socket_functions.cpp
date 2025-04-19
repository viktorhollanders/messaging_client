#include "common/socket_functions.h"
#include "common/check_os.h"
#include <cmath>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <iostream>

sockaddr_in create_socket_address(int port,  std::string ip_address) {
      struct sockaddr_in address;
      address.sin_family = AF_INET;
      address.sin_port = htons(port);
      if(ip_address == "") {
          address.sin_addr.s_addr = INADDR_ANY;
      } else {
          address.sin_addr.s_addr = inet_addr(ip_address.c_str());
      }

      return address;
};

socket_t create_socket(sockaddr *address) {

    int socketfd =  socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(socketfd == SOCKET_ERROR_VALUE) {
        std::cout << "Failed to cerate socket" << '\n';
        return SOCKET_ERROR_VALUE;
    }
    return socketfd;
};


bool bind_socket(socket_t &socketfd, const sockaddr *address, socklen_t socket_len) {
    if ( bind(socketfd, address, socket_len) < 0) {
        std::cout << "Binding failed" << std::endl;
        return false;
    }
    return true;
};

bool listen_for_connection(socket_t &socketfd) {

    // The second parameter in listen is the backlog and it indicates
    // how many pending connections the server can have.
    if (listen(socketfd, 5) < 0) {
        std::cout << "Listen failed" << std::endl;
        return false;
    }
    return true;
};

socket_t accept_connection(socket_t socketfd, struct sockaddr *client_addr, socklen_t address_len) {
    socket_t client_socket = accept(socketfd, client_addr, address_len);
    if (client_socket)
     return 0;
};

bool connect_to_server(socket_t socketfd, const sockaddr *address, socklen_t socket_len) {
    if ( connect(socketfd, address, socket_len) < 0) {
        std::cout << "Connection failed" << std::endl;
        return false;
    }
    return true;
};
