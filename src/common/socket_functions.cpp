#include "common/socket_functions.h"
#include "common/check_os.h"
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>

// client and server methods

// Creates a socket address
// If no ip_address is passed in it is set to and empty string
// will throw an error if the IP address is invalid with an error message and
sockaddr_in create_socket_address(int port,  std::string ip_address = "") {
      struct sockaddr_in address{};
      address.sin_family = AF_INET;
      address.sin_port = htons(port);
      if(ip_address == "") {
          address.sin_addr.s_addr = INADDR_ANY;
      } else {
          if (inet_pton(AF_INET, ip_address.c_str(), &address.sin_addr) < 0) {
              throw std::invalid_argument("Invlaid IP address: " + ip_address);
          }
      }
    return address;
};

// Creates a tcp socket
socket_t create_socket(sockaddr *address) {

    int socketfd =  socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(socketfd == SOCKET_ERROR_VALUE) {
        std::cout << "Failed to create socket" << '\n';
        return SOCKET_ERROR_VALUE;
    }
    return socketfd;
};

// Closes a conection
int close_conection(socket_t socketfd) {

    #ifdef _WIN32
        // Windows-specific socket closing
        if (closesocket(socketfd) != 0) {
            std::cerr << "Error closing socket: " << GET_SOCKET_ERROR << std::endl;
            return -1;
        }
    #else
        // UNIX/Linux/macOS socket closing
        if (close(socketfd) < 0) {
            std::cerr << "Error closing socket: " << strerror(errno) << std::endl;
            return -1;
        }
    #endif

    return 0;
};


// Server methods

// Binds a socket
bool bind_socket(socket_t &socketfd, const sockaddr *address, socklen_t socket_len) {
    if ( bind(socketfd, address, socket_len) < 0) {
        std::cout << "Binding failed" << std::endl;
        return false;
    }
    return true;
};

// Listens for a connection
bool listen_for_connection(socket_t &socketfd) {

    // The second parameter in listen is the backlog and it indicates
    // how many pending connections the server can have.
    if (listen(socketfd, 5) < 0) {
        std::cout << "Listen failed" << std::endl;
        return false;
    }
    return true;
};

// Creates a connection
int accept_connection(socket_t socketfd, struct sockaddr *client_addr, socklen_t *address_len) {
    socket_t client_socket = accept(socketfd, client_addr, address_len);
    if (client_socket < 0) {
        return -1;
    }

    return client_socket;
};
// client methods

// Connects to a server
bool connect_to_server(socket_t socketfd, const sockaddr *address, socklen_t socket_len) {
    if ( connect(socketfd, address, socket_len) < 0) {
        std::cout << "Connection failed" << std::endl;
        return false;
    }
    return true;
};
