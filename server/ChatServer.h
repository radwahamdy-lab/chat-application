#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#include <boost/asio.hpp>
using boost::asio::ip::tcp;

#include "ClientSession.h"
#include "../common/Message.h"
#include "../database/UserRepo.h"

class ChatServer {
    public:
        boost::asio::ip::tcp::acceptor acceptor;
        vector<ClientSession> clients;
        vector<string> usrnames;
        UserRepo users;
        ChatServer(boost::asio::io_context io) {
            acceptor(io, tcp::endpoint(tcp::v4(), 13));
            startAccept(io);
        }
        void startAccept(boost::asio::io_context io, string client_username, string stat){
            //create socket - call async accept - suc -> create cli sess + start() then loop
            tcp::socket socket(io);
            acceptor.accept(socket);
            ClientSession client(this, io, client_username);
            Msg enter_msg;
            if(stat=="login")
                enter_msg{MsgType::LOGIN, client_username, "server", ""};
            else if(stat=="register")
                enter_msg{MsgType::REGISTER, client_username, "server", ""};
            handleMsg(client, log, client_username);
            startAccept(io);
        }
        void registerClient(string usrname, ClientSession client){
            clients.push_back(client);
            usrnames.push_nack(usrname);
            
            Msg status_update{MsgType::STATUS, usrname, "all", "online"};
            handleMsg(client, status_update, usrname);
        }
        void handleMsg(ClientSession client, Msg msg, string usrname){
            switch(msg.type){
                case MsgType::LOGIN:
                    if(userRepo.validateUser(..)){
                        registerClient(usrname, client);
                    } else {
                        Msg error{MsgType::ERROR, usrname, usrname, "User cannot be found"};
                        handleMsg(client, error, usrname);
                    }
                case MsgType::REGISTER:
                    userRepo.createUser();
                case MsgType::CHAT:
                    vector<string>::Iterator it = find(usrnames.begin(), usrnames.end(), msg.receiver);
                    if(it != usrnames.end()){
                        // int rec_index = it - usrnames.begin();
                        // string rec_usrname = usrnames.at(rec_index);
                        // ClientSession rec = clients.at(rec_index);
                        client.send(msg);
                    } else {
                        Msg error{MsgType::ERROR, usrname, usrname, "Receiver cannot be found"};
                        handleMsg(client, error, usrname);
                    }
                case MsgType::STATUS:
                    client.send(msg);
                case MsgType::ERROR:
                    client.send(msg);
                
            }
        }
        void removeClient(string usrname){
            vector<string>::Iterator it = find(usrnames.begin(), usrnames.end(), usrname);
            int index = it - v.begin();
            Msg status_update{MsgType::STATUS, usrname, "all", "online"};
            handleMsg(clients.at(index), status_update, usrname);
            usrnames.erase(usrnames.begin() + index);
            clients.erase(clients.begin() + index);
        }
}
