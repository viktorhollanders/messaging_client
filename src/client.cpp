#include "asio/connect.hpp"
#include "asio/io_context.hpp"
#include "asio/ip/tcp.hpp"
#include "asio/write.hpp"
#include <asio.hpp>
#include <iostream>
#include <string>
#include <system_error>

void create_user(std::string &username) {
    while(username.empty()) {
        std::cout << "Enter a user name: ";
        getline(std::cin, username);
    }
}

int main(int argc, char *argv[]) {
  try {

    if (argc != 3) {
      std::cerr << "Usage: chat_client <host> <port>\n";
      return 1;
    }

    asio::io_context io_context;

    asio::ip::tcp::socket socket(io_context);
    asio::ip::tcp::resolver resolver(io_context);

    // contect to the server
    asio::connect(socket, resolver.resolve(argv[1], argv[2]));

    // Create user name
    std::string username;
    create_user(username);

    // send some data
    std::string data{};
    std::cout << "enter your message: ";
    std::getline(std::cin, data);

    while (data != "quit") {
        auto format_message = username + ": " + data + "\n";
      auto result = asio::write(socket, asio::buffer(format_message));

      std::cout << "data sent: " << format_message.length() << '/' << result << std::endl;
      std::cout << std::endl;

      std::cout << "enter your message: ";
      std::getline(std::cin, data);
    }

    std::error_code ec;
    socket.shutdown(asio::ip::tcp::socket::shutdown_both, ec);
    if (ec) {
      // Handle error
      std::cerr << "Shutdown error: " << ec.message() << std::endl;
    }
    socket.close();

  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  return 0;
}
