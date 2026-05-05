#pragma once

#include <string>
#include <vector>
#include <map>
using namespace std;

#include <boost/asio.hpp>
using boost::asio::ip::tcp;

#include "../database/Userdb.h"
#include "../common/Message.h"


class ChatServer {
    public:
        ChatServer(string filename, int port);
        void run();
        void startAccept();
        void handleSignUp(Msg, tcp::socket*);
        bool login(string, string, string);
        void getMsg(tcp::socket*);
        void sendMsg(Msg, tcp::socket*);
        void handleLogin(Msg, tcp::socket*);
        void handleLogout(Msg, tcp::socket*);
        void handleClient(Msg, tcp::socket*);
        void sendMsgToAll(Msg);
        void sendMsgToOne(Msg, tcp::socket*);
        void sendUsers(Msg, tcp::socket*);
        void sendChatMsgs(tcp::socket*, string, string);

    private:
        Userdb db;
        boost::asio::io_context io;
        tcp::acceptor acceptor;
        vector<User> users;
        vector<User> activeUsers;
        vector<tcp::socket*> client_sockets;
        map<string, tcp::socket*> activeUsersSockets;

};