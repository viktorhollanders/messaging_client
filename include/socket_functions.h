#ifndef SOCKET_FUNCTIONS_H
#define SOCKET_FUNCTIONS_H

#include <string>
#include "check_os.h"


// server and client
socket_address_in_t create_socket_address(int port,  std::string ip_address = "");
socket_t create_socket(socket_address_t *address);
int close_connection(socket_t socketfd);

// send recieve
int send_message_size(socket_t socketfd, int message_size);
int receive_message_size(socket_t socketfd);

int send_message(socket_t socketfd, std::string message);
int receive_message(socket_t socketfd, std::string& message, int message_lenght);

// server
int bind_socket(socket_t socketfd, const socket_address_t *address, address_size_t socket_len);
int listen_for_connection(socket_t socketfd);
socket_t accept_connection(socket_t socketfd, socket_address_t *client_addr, address_size_t *address_len);

// client
int connect_to_server(socket_t socketfd, const socket_address_t *address, address_size_t socket_len);

#endif // end SOCKETS_FUNCTIONS_H
