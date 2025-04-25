#ifndef CLIENT_INFO_H
#define CLIENT_INFO_H

#include <ctime>
#include <string>


class ClientInfo {
    private:
    std::string username;
    std::string connection_timestamp;

    public:
    ClientInfo(std::string username);
    ~ClientInfo();

    std::string get_username();
    void set_username(std::string new_usernmae);
    void set_connection_timestamp( std::string new_connection_timestamp);
    std::string get_connection_timestamp();
};

#endif
