#include <cstdlib>
#include <iostream>
#include "common/check_os.h"
#include "common/socket_functions.h"


int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Please provide address and port for server" << std::endl;
        return -1;
    }

    std::string ip = argv[1];
    int port = atoi(argv[2]);

    socket_address_in_t address = create_socket_address(port, ip);
    socket_t serverfd = create_socket((socket_address_t *) &address);
    address_size_t addSize =  sizeof(address);

    if (bind_socket(serverfd, (socket_address_t *) &address, addSize)) {
        std::cout << "Bind failed" << std::endl;
        close_connection(serverfd);
        return -1;
    }



    if (listen_for_connection(serverfd)) {
        std::cout << "Connection failed" << std::endl;
        close_connection(serverfd);
        return -1;
    }


    std::cout << "Server listening on: " << ip << " port: " << port  << std::endl;
    socket_t server_socket = accept_connection(serverfd, (socket_address_t *) &address, &addSize);

    while(true) {
        if (server_socket < 0) {
        std::cout << "Return error to client" << "\n";

        } else {

        std::cout << "Acepting conections " << "\n";
        }

    }


    return 0;
}
