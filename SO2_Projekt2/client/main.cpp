#include "ChatClient.h"
#include <boost/asio.hpp>
#include <iostream>
#include <conio.h>

int main() {
    try {
        // create asio context
        boost::asio::io_context io_context;

        // initialize the client
        ChatClient client(io_context, "127.0.0.1", 12345);
        client.start();
    } catch(std::exception& e) {
        std::cerr << "\033[31mError: could not connect to the server\n\033[0m";
        std::cout << "\033[33mPress any key to continue...\033[0m";
        getch();
    }

    return 0;
}