#include "ChatServer.h"
#include <iostream>

int main() {
    try {
        // set up a port
        unsigned short port = 12345;

        // create asio context
        boost::asio::io_context io_context;

        // initialize a server
        ChatServer server(io_context, port);
        server.startAccept();
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "\033[31mError: " << e.what() << "\033[0m\n";
        return 1;
    }

    return 0;
}