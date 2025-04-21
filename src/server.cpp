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
    bind_socket(serverfd, (socket_address_t *) &address, sizeof(address));

    if (!listen_for_connection(serverfd)) {
        std::cout << "connection failed" << std::endl;
    }
    std::cout << "Listening!!" << std::endl;


    return 0;
}
