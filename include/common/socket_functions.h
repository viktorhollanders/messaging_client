#ifndef SOCKET_FUNCTIONS_H
#define SOCKET_FUNCTIONS_H

#include "check_os.h"
#include <string>


sockaddr_in create_socket_address(int port,  std::string ip_address);
socket_t create_socket(sockaddr *address);
bool bind_socket(socket_t &socketfd, const sockaddr *address, socklen_t socket_len);
bool listen_for_connection(socket_t &socketfd);
int accept_connection(socket_t socketfd, struct sockaddr *client_addr, socklen_t *address_len);
int close_conection(socket_t socketfd);
bool connect_to_server(socket_t socketfd, const sockaddr *address, socklen_t socket_len);
void disconnect_from_server();

#endif // end SOCKETS_FUNCTIONS_H
