#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#include <boost/asio.hpp>
using boost::asio::ip::tcp;

#include "../common/Message.h"
#include "../database/UserRepo.h"

class ClientSession;

class ChatServer {
    public:
        boost::asio::ip::tcp::acceptor acceptor;
        vector<ClientSession *> clients;
        vector<string> usrnames;
        UserRepo users;
        ChatServer(boost::asio::io_context &io, int port);
        void startAccept(boost::asio::io_context &io);
        void registerClient(string usrname, ClientSession &client);
        void handleMsg(ClientSession &client, Msg msg);
        void removeClient(string usrname);
};
