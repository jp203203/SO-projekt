#ifndef SO2_PROJEKT2_CHATCLIENT_H
#define SO2_PROJEKT2_CHATCLIENT_H

#include <boost/asio.hpp>
#include <thread>
#include <atomic>
#include <string>

class ChatClient {
public:
    ChatClient(boost::asio::io_context& io_context, const std::string& host, unsigned short port);
    void start();

private:
    void readFromServer();
    void writeToServer();

    boost::asio::ip::tcp::socket socket_;
    std::atomic<bool> connected_;
};


#endif //SO2_PROJEKT2_CHATCLIENT_H
