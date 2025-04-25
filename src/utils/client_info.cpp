#include <string>
#include "client_info.h"

ClientInfo::ClientInfo(std::string username) : username(username) {}

ClientInfo::~ClientInfo() {};

std::string ClientInfo::get_username() { return username; };
void ClientInfo::set_username(std::string new_usernmae) {
    username = new_usernmae;
};

void ClientInfo::set_connection_timestamp( std::string new_connection_timestamp) {
    connection_timestamp = new_connection_timestamp;
};

 std::string ClientInfo::get_connection_timestamp() {
    return connection_timestamp;
};
