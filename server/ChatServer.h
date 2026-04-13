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

class ChatServer
{
public:
    boost::asio::ip::tcp::acceptor acceptor;
    vector<ClientSession *> clients;
    vector<string> usrnames;
    UserRepo users;
    ChatServer(boost::asio::io_context &io, int port)
    {
        acceptor(io, tcp::endpoint(tcp::v4(), port));
        startAccept(io);
    }
    void startAccept(boost::asio::io_context &io)
    {
        ClientSession *client = new ClientSession(this, io);

        acceptor.async_accept(
            client->socket,
            [this, client, &io](boost::system::error_code ec) {
                    if (!ec) {
                        clients.push_back(client);
                        client->start();
                    }
                    else delete client;
                                  
                startAccept(io); // continue accepting
            });
    }
    void registerClient(string usrname, ClientSession &client)
    {
        clients.push_back(&client);
        usrnames.push_back(usrname);

        Msg status_update{MsgType::STATUS, usrname, "all", "online"};
        handleMsg(client, status_update);
    }
    void handleMsg(ClientSession &client, Msg msg)
    {
        switch (msg.type)
        {
        case MsgType::LOGIN:
            if (users.validateUser(msg.sender, msg.content))
            {
                registerClient(msg.sender, client);
                client.usrname = msg.sender;
            }
            else
            {
                Msg error{MsgType::ERROR, "server", usrname, "User cannot be found"};
                client.send(error);
            }
            break;
        case MsgType::REGISTER:
            userRepo.createUser(msg.sender, msg.content);
            break;
        case MsgType::CHAT:
            vector<string>::iterator it = find(usrnames.begin(), usrnames.end(), msg.receiver);
            if (it != usrnames.end())
            {
                int rec_index = it - usrnames.begin();
                string rec_usrname = usrnames.at(rec_index);
                ClientSession* rec = clients.at(rec_index);
                rec->send(msg);
            }
            else
            {
                Msg error{MsgType::ERROR, "server", usrname, "Receiver cannot be found"};
                client.send(error);
            }
            break;
        case MsgType::STATUS:
            for (int i = 0; i < clients.size(); i++)
            {
                clients[i]->send(msg);
            }
            break;
        }
    }
    void removeClient(string usrname)
    {
        vector<string>::iterator it = find(usrnames.begin(), usrnames.end(), usrname);
        int index = it - usrnames.begin();
        if(it != usrnames.end()){
            Msg status_update{MsgType::STATUS, usrname, "all", "offline"};
            handleMsg(*(clients.at(index)), status_update);

            usrnames.erase(usrnames.begin() + index);
            delete clients[index];
            clients.erase(clients.begin() + index);
        }
    }
}
