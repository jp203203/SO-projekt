#include "ChatClient.h"
#include <iostream>

ChatClient::ChatClient(boost::asio::io_context& io_context, const std::string& host, unsigned short port)
    : socket_(io_context),
      connected_(false)
{
    // create resolver object and translate the hostname and port number to list of possible endpoints
    boost::asio::ip::tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(host, std::to_string(port));
    // attempt to connect to the server
    boost::asio::connect(socket_, endpoints);
    connected_ = true;
}

// starts two threads for receiving and sending messages, and stops them if client disconnects from the server
void ChatClient::start() {
    // threads for simultaneous reading and writing
    std::thread reader(&ChatClient::readFromServer, this);
    std::thread writer(&ChatClient::writeToServer, this);
    std::cout << "\033[35mSend /Q to disconnect\033[0m\n";

    writer.join();
    if(socket_.is_open()) {
        connected_ = false;
        socket_.close();
    }
    reader.join();
}


// reads messages from the server
void ChatClient::readFromServer() {
    try {
        char data[512];
        while(connected_) {
            boost::system::error_code error;
            // reads message
            size_t length = socket_.read_some(boost::asio::buffer(data), error);
            if(error) {
                std::cout << "\033[31mDisconnected from the server.\033[0m\n";
                connected_ = false;
                break;
            }

            // displays the message
            std::string message(data, length);

            std::cout << message;
            std::cout.flush();

        }
    } catch(...) {
        std::cout << "\033[31mError reading from server.\033[0m\n";
    }
}

// responsible for sending messages to the server
void ChatClient::writeToServer() {
    try {
        while(connected_) {
            std::string line;
            // checks if line is read correctly
            if(!std::getline(std::cin, line)) {
                connected_ = false;
                break;
            }
            // sends the message to the server if it's not empty (if user presses the enter key without typing anything)
            if(!line.empty()) {
                if(line == "/q" || line == "/Q") {
                    connected_ = false;
                    socket_.close();
                    break;
                }
                boost::asio::write(socket_, boost::asio::buffer(line + "\n"));
            }
        }
    } catch(...) {
        std::cout << "\033[31mError writing to sever\033[0m\n";
    }
}