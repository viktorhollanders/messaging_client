#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>
#include <map>
#include <mutex>
#include "check_os.h"
#include "socket_functions.h"
#include "client_info.h"

void add_client(socket_t client_socket, std::map<socket_t, ClientInfo>& clients, int& number_of_connections, std::mutex& connection_mutex) {
    std::string username;
    int name_length = receive_message_size(client_socket);

    receive_message(client_socket, username, name_length);
    clients.emplace(client_socket, username);
    std::lock_guard<std::mutex> lock(connection_mutex);
    number_of_connections++;
    std::cout << "Num connections: " << number_of_connections << std::endl;
}

void disconect_client(socket_t client_socket, std::map<socket_t, ClientInfo>& clients, int& number_of_connectinos, std::mutex& connection_mutex) {
    std::cout << "Client disconected " << std::endl;
    std::lock_guard<std::mutex> lock(connection_mutex);
    number_of_connectinos--;
    std::cout << "Num connections: " << number_of_connectinos << std::endl;
    return;
}

void brodcast_message(socket_t client_socket, const std::string message, std::map<socket_t, ClientInfo>& clients, std::mutex& connection_mutex) {

    std::string username;

    {
        std::lock_guard<std::mutex> lock(connection_mutex);
        username = clients.at(client_socket).get_username();
    }

    std::string formated_message = username + ": " + message;

    {
        std::lock_guard<std::mutex> lock(connection_mutex);
        for(const auto& pair : clients) {

            if (pair.first != client_socket) {
                send_message_size(pair.first, formated_message.length());
                send_message(pair.first, formated_message);
            }
        }
    }
    std::cout << "Message brodcasted: " << message << std::endl;
}

void handle_client_messages(socket_t client_socket, std::map<socket_t, ClientInfo>& clients, int& number_of_connectinos, std::mutex& connection_mutex) {
    while(true) {
        int message_length = receive_message_size(client_socket);

        if (message_length < 0) {
            disconect_client(client_socket, clients, number_of_connectinos, connection_mutex);
            break;
        }

        std::string message;
        receive_message(client_socket, message, message_length);
        brodcast_message(client_socket, message, clients, std::ref(connection_mutex));
    }
};

void server_loop(socket_t serverfd) {
    std::map<socket_t, ClientInfo> clients;
    int number_of_connections = 0;
    std::mutex connection_mutex;
    std::vector<std::thread> client_threads;

    while(true) {
        socket_address_t client_address;
        address_size_t client_address_size = sizeof(client_address);


        socket_t new_client_socket = accept_connection(serverfd, (socket_address_t *) &client_address, &client_address_size);
        add_client(new_client_socket, clients, number_of_connections, connection_mutex);
        client_threads.emplace_back(std::thread(handle_client_messages, new_client_socket,
                                           std::ref(clients), std::ref(number_of_connections),
                                           std::ref(connection_mutex)));
                                        client_threads.back().detach();
    }
}

int main(int argc, char *argv[]) {

    if (argc < 3) {
        std::cerr << "Please provide address and port for server" << std::endl;
        return -1;
    }

    std::string ip = argv[1];
    int port = atoi(argv[2]);

    socket_address_in_t address = create_socket_address(port, ip);
    socket_t serverfd = create_socket((socket_address_t *) &address);
    if (serverfd == SOCKET_ERROR_VALUE) {
        std::cout << "Failed to create socket" << std::endl;
        return -1;
    }


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

    server_loop(serverfd);

    close_connection(serverfd);
    return 0;
}
