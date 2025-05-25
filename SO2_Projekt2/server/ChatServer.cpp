#include "ChatServer.h"
#include <iostream>

ChatServer::ChatServer(boost::asio::io_context& io_context, unsigned short port)
    : io_context_(io_context),
      acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
    std::cout << "\033[35mServer is listening...\033[0m\n";
}

// initializes incoming connection acceptance
void ChatServer::startAccept() {
    // create new socket for an upcoming client, based on io_context_
    auto socket = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);

    // accept new connection asynchronously
    acceptor_.async_accept(*socket, [this, socket](const boost::system::error_code& ec) {
        if(!ec) {
            std::thread(&ChatServer::handleClient, this, socket).detach();
        }
        // continue accepting new connections
        startAccept();
    });
}

// checks if user's username is taken
bool ChatServer::isUsernameTaken(const std::string& username) {
    std::lock_guard<std::mutex> lock(clients_mutex_);
    return clients_.find(username) != clients_.end();
}

// sends a message to every user, optionally ignores the specified user
boost::system::error_code ChatServer::broadcastMessage(const std::string& message, const std::string& username="") {
    boost::system::error_code error;

    // locks the access to client sockets
    std::lock_guard<std::mutex> lock(clients_mutex_);
    for (const auto &[name, client_socket]: clients_) {
        if (name != username && client_socket->is_open()) {
            boost::asio::write(*client_socket, boost::asio::buffer(message), error);
        }
    }
    // also log the message on the server
    std::cout << message;

    return error;
}

// handles incoming messages from the client and broadcasts to others
void ChatServer::handleClient(const std::shared_ptr<boost::asio::ip::tcp::socket>& socket) {
    try {
        std::string username;
        boost::system::error_code error;
        char data[512];

        // loop to obtain a unique username
        while(true) {
            std::string un_prompt = "\033[33mEnter a username:\033[0m ";
            boost::asio::write(*socket, boost::asio::buffer(un_prompt), error);
            if(error) return;

            size_t len = socket->read_some(boost::asio::buffer(data), error);
            if(error) return;

            // clean input by removing \n and \r characters
            username = std::string(data, len);
            username.erase(std::remove(username.begin(), username.end(), '\n'), username.end());
            username.erase(std::remove(username.begin(), username.end(), '\r'), username.end());

            if(username.empty()) continue; // ignore empty names

            // add client to the list if username is not taken
            if (!isUsernameTaken(username)) {
                {
                    std::lock_guard<std::mutex> lock(clients_mutex_);
                    clients_[username] = socket;
                }
                // send a welcome message to the user
                std::string welcome_msg = "\033[33mWelcome, " + username + "!\033[0m\n"; // welcome message
                boost::asio::write(*socket, boost::asio::buffer(welcome_msg), error);

                // send a message about user joining the chat
                std::string joined_msg = "\033[33mUser " + username + " joined the chat.\033[0m\n";
                error = broadcastMessage(joined_msg, username);

                break; // if username accepted, exit loop
            } else {
                std::string taken_msg = "\033[31mUsername already taken, try another.\033[0m\n";
                boost::asio::write(*socket, boost::asio::buffer(taken_msg), error);
            }
        }

        // listen for messages from the user and send them to all connected clients
        for(;;) {
            size_t length = socket->read_some(boost::asio::buffer(data), error);
            if(error) {
                // if error, send a message about user disconnecting
                std::string left_msg = "\033[33mUser " + username + " left the chat.\033[0m\n";
                error = broadcastMessage(left_msg, username);

                break;
            }

            // add prefix with username to the message
            std::string message = "\033[3;32m" + username + ":\033[0m " + std::string(data, length);
            error = broadcastMessage(message);
        }
    } catch(...) {
        std::cerr << "\033[31mClient error or disconnected.\033[0m\n";
    }

    // remove the disconnected client from the list
    std::lock_guard<std::mutex> lock(clients_mutex_);
    for(auto it = clients_.begin(); it != clients_.end(); ++it) {
        if(it->second == socket) {
            clients_.erase(it);
            break;
        }
    }
}