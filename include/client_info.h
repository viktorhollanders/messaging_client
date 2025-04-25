#include <ctime>
#include <string>


class ClientInfo {
    private:
    std::string username;
    time_t connection_timestamp;

    public:
    ClientInfo(std::string username, time_t connection_timestamp);
    ~ClientInfo();

    std::string get_username();
    void set_username(std::string new_usernmae);
    void set_connection_timestamp(time_t new_connection_timestamp);
    time_t get_connection_timestamp();
};
