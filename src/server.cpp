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

    while(true) {
        std::cout << "Wait connectoin" << std::endl;
        socket_t new_client_cocket = accept_connection(serverfd, (socket_address_t *) &address, &addSize);
        std::cout << "Connection accepted!" << std::endl;


        int message_length = receive_message_size(new_client_cocket);
        std::string message;

        std::cout << "Message lenght:" << message_length << std::endl;

        int respons_code = receive_message(new_client_cocket, message, message_length);
        std::cout << "Response code: " << respons_code << std::endl;

        std::cout << message << std::endl;
    }

    return 0;
}
