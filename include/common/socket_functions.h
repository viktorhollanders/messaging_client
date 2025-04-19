#ifndef SOCKET_FUNCTIONS_H
#define SOCKET_FUNCTIONS_H

#include <string>
#include "check_os.h"

sockaddr_in create_socket_address(sockaddr *address,int port, std::string ip_address = "");
socket_t create_socket(sockaddr *address);
bool bind_socket(socket_t &socket, sockaddr *address, socklen_t socket_len);
bool listen_for_connection(socket_t &socket);
bool aaccept_connection(socket_t socketfd, struct sockaddr *client_addr, socklen_t address_len);
bool connect_to_server(socket_t socket, sockaddr &socket_address);

#endif // end SOCKETS_FUNCTIONS_H
