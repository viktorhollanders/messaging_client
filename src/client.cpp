#include <cstdlib>
#include <iostream>
#include "common/check_os.h"
#include "common/socket_functions.h"

int main(int argc, char *argv[]) {

    if (argc < 3) {
        std::cout << "Pleas provide a address and a port for for the client to conect to" << "\n";
    }

    std::string ip = argv[1];
    int port = atol(argv[2]);
    socket_address_in_t address = create_socket_address(port, ip);
    socket_t clientfd = create_socket((socket_address_t *) &address);
    address_size_t addSize =  sizeof(address);

    if (connect_to_server(clientfd, (socket_address_t *) &address, addSize)) {
        std::cout << "Connection failed" << std::endl;
        close_connection(clientfd);
        return -1;
    }

    std::string message;
    std::cout << "Enter your message: ";

    while(message != "quit") {

    }

    close_connection(clientfd);

    return 0;
}
