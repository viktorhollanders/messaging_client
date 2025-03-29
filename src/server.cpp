#include "asio/io_context.hpp"
#include "asio/ip/tcp.hpp"
#include "asio/read_until.hpp"
#include "asio/streambuf.hpp"
#include <asio.hpp>
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <system_error>

using namespace asio::ip;

class session : public std::enable_shared_from_this<session> {
public:
  session(asio::ip::tcp::socket socket) : m_socket(std::move(socket)) {}

  void run() { wait_for_request(); }

private:
  void wait_for_request() {
    auto self(shared_from_this());
    std::cout << "Waiting..." << std::endl;
    asio::async_read_until(
        m_socket, m_buffer, "\n",
        [this, self](std::error_code ec, std::size_t) {
          if (!ec) {

            std::string data{std::istreambuf_iterator<char>(&m_buffer),
                             std::istreambuf_iterator<char>()};
            std::cout << data << std::endl;

            wait_for_request();
          } else {
                std::cout << "run when client leavs" << std::endl;
            std::cout << "error: " << ec.message() << std::endl;
          }
        });
  }

private:
  asio::ip::tcp::socket m_socket; // Fixed typo here
  asio::streambuf m_buffer;
};

class server {
public:
  server(asio::io_context& io_context,
      const tcp::endpoint& endpoint)
      : m_acceptor(io_context, endpoint) {
    do_accept();
  }

private:
  void do_accept() {
    m_acceptor.async_accept([this](std::error_code ec, tcp::socket socket) {
      if (!ec) {
        std::make_shared<session>(std::move(socket))->run();
      }
      do_accept();
    });
  }

  tcp::acceptor m_acceptor;
};

int main(int argc, char *argv[]) {
  try {

      if (argc < 2)
      {
        std::cerr << "Usage: server <port> \n";
        return 1;
      }

    std::cout << "Server started!!!" << std::endl;
    asio::io_context io_context;

    asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), std::atoi(argv[1]));
    server message_server(io_context, endpoint);

    io_context.run();
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
  return 0;
}
