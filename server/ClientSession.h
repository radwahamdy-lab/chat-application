#pragma once
#include <boost/asio.hpp>
using boost::asio::ip::tcp;

#include <string>
using namespace std;

#include "../common/Serializer.h"

class ChatServer;

class ClientSession {
    public:
        tcp::socket socket;
        ChatServer* server;
        string usrname;
        string msg_str;
        array<char, 128> buf;

        ClientSession(ChatServer &serv, boost::asio::io_context &io);
        void start();
        void doRead();
        void send(Msg msg);
};