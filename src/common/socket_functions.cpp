#include "common/socket_functions.h"
#include "common/check_os.h"
#include <sys/socket.h>


// server and client

// Creates a socket address
// If no ip_address is passed in it is set to and empty string
// will throw an error if the IP address is invalid with an error message and
socket_address_in_t create_socket_address(int port,  std::string ip_address) {
      struct sockaddr_in address{};
      address.sin_family = AF_INET;
      address.sin_port = htons(port);
      if(ip_address == "") {
          address.sin_addr.s_addr = INADDR_ANY;
      } else {
          if (inet_pton(AF_INET, ip_address.c_str(), &address.sin_addr) < 0) {
              throw std::invalid_argument("Invalid IP address: " + ip_address);
          }
      }
    return address;
}

// Creates a tcp socket
socket_t create_socket(socket_address_t *address) {
    socket_t socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(socketfd == SOCKET_ERROR_VALUE) {
        std::cerr << "Failed to create socket" << '\n';
        return SOCKET_ERROR_VALUE;
    }
    return socketfd;
}
// Sends the size of the message
int send_message_size(socket_t socketfd, int message_size) {
    int size = htonl(message_size);
    int resault = send(socketfd, &size, sizeof(size), 0);
    if (resault < 0) {
        std::cout << "Error sending message size: " << GET_SOCKET_ERROR << std::endl;
        return -1;
    }
    return 0;
};

// Receives the size of the message
int receive_message_size(socket_t socketfd) {
    int size_net_order;
    int bytes_recived = recv(socketfd,  &size_net_order, sizeof(size_net_order), 0);

    if (bytes_recived != size_net_order) {
        std::cerr << "Error receiving message size: " << GET_SOCKET_ERROR << std::endl;
        return -1;
    }

    return ntohl(size_net_order);
};

// Sends the message
int send_message(socket_t socketfd, std::vector<char> message) {
    int result = send(socketfd, message.data(), message.size(), 0);

    if (result < 0) {
        std::cout << "Error sending message" << GET_SOCKET_ERROR << std::endl;
        return -1;
    }

    return 0;
};

// Recieves the message
// Need message size that is obtained by receive_message_size()
//  and use that the third argument in receive_message
int receive_message(socket_t socketfd, std::vector<char>& message, int message_size) {
    message.resize(message_size);

    int recived_code = recv(socketfd, message.data(), message_size, 0);
    return recived_code;
};

// Closes a conection
int close_connection(socket_t socketfd) {

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
}

// Server

// Binds a socket
int bind_socket(socket_t socketfd, const socket_address_t *address, address_size_t socket_len) {
    if (bind(socketfd, address, socket_len) < 0) {
        std::cerr << "Binding failed" << std::endl;
        return -1;
    }
    return 0;
}

// Listens for a connection
int listen_for_connection(socket_t socketfd) {
    // The second parameter in listen is the backlog and it indicates
    // how many pending connections the server can have.
    if (listen(socketfd, 5) < 0) {
        std::cerr << "Listen failed" << std::endl;
        return -1;
    }
    return 0;
}

// Creates a connection
socket_t accept_connection(socket_t socketfd, socket_address_t *client_addr, address_size_t *address_len) {
    socket_t client_socket = accept(socketfd, client_addr, address_len);
    if (client_socket < 0) {
        return SOCKET_ERROR_VALUE;
    }
    return client_socket;
}
// client

// Connects to a server
int connect_to_server(socket_t socketfd, const socket_address_t *address, address_size_t socket_len) {
    if ( connect(socketfd, address, socket_len) < 0) {
        std::cerr << "Connection failed" << std::endl;
        return -1;
    }
    return 0;
}
