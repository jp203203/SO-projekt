#ifndef SO2_PROJEKT2_CHATSERVER_H
#define SO2_PROJEKT2_CHATSERVER_H

#include <boost/asio.hpp>
#include <thread>
#include <vector>
#include <memory>
#include <mutex>

class ChatServer {
public:
    ChatServer(boost::asio::io_context& io_context, unsigned short port);
    void startAccept();

private:
    void handleClient(const std::shared_ptr<boost::asio::ip::tcp::socket>& socket);
    bool isUsernameTaken(const std::string& username);
    boost::system::error_code broadcastMessage(const std::string& username, const std::string& message);

    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::io_context& io_context_;
    std::unordered_map<std::string, std::shared_ptr<boost::asio::ip::tcp::socket>> clients_;
    std::mutex clients_mutex_;
};


#endif //SO2_PROJEKT2_CHATSERVER_H
