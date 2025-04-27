#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>
#include "check_os.h"
#include "socket_functions.h"

void client_send(socket_t &clientfd) {
    std::string message;
    // std::cout << "Enter your message: ";
    std::getline(std::cin, message);

    while(message != "quit") {
        send_message_size(clientfd, message.length());
        send_message(clientfd, message);

        // std::cout << "Enter your message: ";
        std::getline(std::cin, message);
    }
}

void client_receive(socket_t &clientfd) {
    while(true) {
        int message_length = receive_message_size(clientfd);

        if (message_length < 0) {
            break;
        }

        std::string message;
        receive_message(clientfd, message, message_length);
        std::cout << message << std::endl;
    }

}

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

    std::string username;
    std::cout << "Enter your username: ";
    std::getline(std::cin, username);
    if (username.length() == 0) {
        username = "User";
    };
    send_message_size(clientfd, username.length());
    send_message(clientfd, username);

    std::thread send_thread(client_send, std::ref(clientfd));
    std::thread receive_thread(client_receive, std::ref(clientfd));
    send_thread.join();


    close_connection(clientfd);

    return 0;
}
