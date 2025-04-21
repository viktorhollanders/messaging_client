#ifndef SOCKET_FUNCTIONS_H
#define SOCKET_FUNCTIONS_H

#include "check_os.h"
#include <string>

// server and client
socket_address_in_t create_socket_address(int port,  std::string ip_address = "");
socket_t create_socket(socket_address_t *address);
int close_connection(socket_t socketfd);

// server
bool bind_socket(socket_t socketfd, const socket_address_t *address, address_size_t socket_len);
bool listen_for_connection(socket_t socketfd);
socket_t accept_connection(socket_t socketfd, socket_address_t *client_addr, address_size_t *address_len);

// client
bool connect_to_server(socket_t socketfd, const socket_address_t *address, address_size_t socket_len);

#endif // end SOCKETS_FUNCTIONS_H
