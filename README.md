# Messaging client (v1.0)

## Author
Viktor Hollanders
<viktorhollanders@hey.com>

## About
This is a simple messaging client built in C++ 11. It uses the TCP/IP protocol for client server communication. The app runs in the terminal and allows multiple clients to connect to a central server. For this project no libraries are used. I implemented the socket operations from scratch.
Clients can see their own messages and when they receive a message they can see from who it is.
It is cross platform so it can run on Linux and Mac and should be able to run on Windows but that has not been tested.
Some future improvements would be:

- Adding that clients can see the number of connected clients.
- See when someone joins the server.
- Persistent storage.

## Requirements
- C++ 11
- No additional libraries required

## Building
To build the app run:
```sh
  make
```

To start a server:
```sh
./bin/server [address] [port]
```

To start a client:
```sh
./bin/client [address] [port]
```

To quit a client simply type quit.
The client and server can also be compiled separately:
```sh
  make server
```

```sh
  make client
```

To clean up you can run:
```sh
  make clean
```

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
