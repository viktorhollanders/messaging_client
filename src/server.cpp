#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>
#include <map>
#include "check_os.h"
#include "socket_functions.h"
#include "client_info.h"




int main(int argc, char *argv[]) {
    std::vector<std::thread> client_threads;
    std::map<int, ClientInfo> clients;
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

    int number_of_connectinos = 0;

    while(true) {
        std::cout << "Wait connectoin" << std::endl;
        socket_t new_client_cocket = accept_connection(serverfd, (socket_address_t *) &address, &addSize);
        client_threads.emplace_back(new_client_cocket);
        number_of_connectinos += 1;

        std::cout << "Conected clients: " << number_of_connectinos << std::endl;
        bool client_connected = true;

        while(client_connected) {
            int message_length = receive_message_size(new_client_cocket);

            if (message_length < 0) {
                std::cout << "Client dissconected: " << std::endl;
                number_of_connectinos -= 1;
                client_connected = false;
                break;
            }


            std::string message;
            receive_message(new_client_cocket, message, message_length);

            std::cout << message << std::endl;
        }

    }
    return 0;
}
