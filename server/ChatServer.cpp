#include <string>
#include <sstream>
#include <iostream>
using namespace std;
#include <boost/asio.hpp>
using boost::asio::ip::tcp;

#include "ChatServer.h"
#include "../database/Userdb.h"
#include "../database/User.h"
#include "../common/Serializer.h"
#include "../common/Message.h"


ChatServer::ChatServer(string filename, int port) : db(filename), acceptor(io, tcp::endpoint(tcp::v4(), port)){
    users = db.getUsers();
    startAccept();
}

void ChatServer::run(){
    io.run();
}

void ChatServer::startAccept(){
    tcp::socket* socket = new tcp::socket(io);
    acceptor.async_accept(*socket, [this, socket](boost::system::error_code ec) {
        cout << "Listening.." << endl;
        if(!ec){
            client_sockets.push_back(socket);
            getMsg(socket);
        }
        startAccept();
    });
}

// For Login and Sign Up
void ChatServer::handleLogin(Msg msg, tcp::socket* socket){

    // Parsing msg content to get credentials
    stringstream ss(msg.content);
    string usrname;
    string email;
    string password;
    getline(ss, usrname, ',');
    getline(ss, email, ',');
    getline(ss, password, ',');
    User activeUser;
    activeUser.usrname = usrname;
    activeUser.email = email;
    activeUser.password = password;

    // Handling Request
    bool status = login(usrname, email, password);

    // Adding Client
    Msg login_request_reply;
    login_request_reply.type = MsgType::LOGIN;
    login_request_reply.sender = "server";
    login_request_reply.receiver = usrname;
    if(status){
        login_request_reply.content = "login successful";
        activeUsers.push_back(activeUser);
        for(int i=0; i<activeUsers.size(); i++) cout << activeUsers[i].usrname << ",";
        handleMsg(login_request_reply, socket);

        Msg status_update;
        status_update.type = MsgType::STATUS;
        status_update.sender = usrname;
        status_update.receiver = "all";
        status_update.content = "online";
        handleMsg(status_update, socket);
    } else {
        login_request_reply.content = "login unsuccessful";
        sendMsg(login_request_reply, socket);
    }

}

void ChatServer::handleMsg(Msg msg, tcp::socket* socket) {
    tcp::socket* rec_socket;
    if(msg.receiver == "all"){
        for(int i=0; i<client_sockets.size(); i++){
            if(client_sockets[i] != socket)
                sendMsg(msg, client_sockets[i]);
        } 
    } else {
        bool active = false;
        for(int i=0; i<activeUsers.size() && !active; i++){
            if(activeUsers[i].usrname == msg.receiver){
                rec_socket = client_sockets[i];
                sendMsg(msg, rec_socket);
                active = true;
            }
        }
        cout << "active: " << active << endl;
        if (!active) {
            bool found = false;
            users = db.getUsers();
            for(int i=0; i<users.size() && !found; i++){
                if(users[i].usrname == msg.receiver)
                    found = true;
            }
            if(!found){
                Msg error;
                error.type = MsgType::ERR;
                error.sender = "server";
                error.receiver = msg.sender;
                error.content = msg.receiver + " cannot be found";
                sendMsg(error, socket);
            }
            
        }
    }
}

void ChatServer::sendMsg(Msg msg, tcp::socket* socket) {
    string msg_str = serialize(msg);
    boost::asio::async_write(*socket, boost::asio::buffer(msg_str), [](boost::system::error_code ec, size_t len){});
}


void ChatServer::getMsg(tcp::socket* socket){
    char* buf = new char[1024];
    socket->async_read_some(boost::asio::buffer(buf, 1024), [this, socket, buf](boost::system::error_code ec, size_t len){
        if(ec != boost::asio::error::eof) {
            string msg_str(buf, len);
            Msg msg = deserialize(msg_str);
            cout << "msg received by server: " << msg_str << endl;
            if(msg.type == MsgType::LOGIN)
                handleLogin(msg, socket);
            else if(msg.type == MsgType::REGISTER)
                handleSignUp(msg, socket);
            else if(msg.type == MsgType::LOGOUT)
                handleLogout(msg);
            else if(msg.type == MsgType::STATUS)
                handleMsg(msg, socket);
            else if(msg.type == MsgType::CHAT){
                handleMsg(msg, socket);
                db.handleNewMsg(msg);
            }
            else if(msg.type == MsgType::GET_USERS){
                sendUsers(msg, socket);
            }
            else if(msg.type == MsgType::GET_MSGS)
                sendChatMsgs(socket, msg.sender, msg.content);
            getMsg(socket);
        }
    });
}

void ChatServer::handleSignUp(Msg msg, tcp::socket* socket){
    stringstream ss(msg.content);
    string usrname;
    string email;
    string password;
    getline(ss, usrname, ',');
    getline(ss, email, ',');
    getline(ss, password, ',');
    User user;
    user.usrname = usrname;
    user.email = email;
    user.password = password;

    User usr = db.creatUser(usrname, email, password);
    bool status;
    if(db.checkUserExists(usr.usrname))
        status = false;
    else{
        status = db.addUser(usr);
        users.clear();
        users = db.getUsers();
    }

    Msg signUpReply;
    signUpReply.type = MsgType::REGISTER;
    signUpReply.sender = "server";
    signUpReply.receiver = usrname;
    if(status)
        signUpReply.content = "sign up successful";
    else
        signUpReply.content = "sign up unsuccessful";
    sendMsg(signUpReply, socket);
}

void ChatServer::handleLogout(Msg msg){
    int index = -1;
    for(int i=0; i<activeUsers.size() && index==-1; i++)
        if(activeUsers[i].usrname == msg.sender)
            index = i;
    if(index != -1){
        activeUsers.erase(activeUsers.begin() + index);
        client_sockets.erase(client_sockets.begin() + index);
    } else {
        cout << "user is already not found" << endl;
    }
}

bool ChatServer::login(string usrname, string email, string password){
    bool status = db.checkUser(usrname, email, password);
    return status;
}

void ChatServer::sendUsers(Msg msg, tcp::socket* socket){
    Msg usersListMsg;
    usersListMsg.type = MsgType::GET_USERS;
    usersListMsg.sender = "server";
    usersListMsg.receiver = msg.sender;
    string usersList = "";
    for(int i=0; i<users.size(); i++)
        usersList += users[i].usrname + ",";
    usersList += "\n";
    for(int i=0; i<activeUsers.size(); i++)
        usersList += activeUsers[i].usrname + ",";
    usersList += "\n";
    usersListMsg.content = usersList;
    sendMsg(usersListMsg, socket);
}


void ChatServer::sendChatMsgs(tcp::socket* socket, string sender, string receiver){
    vector<string> msgs = db.getMsgsForChat(sender, receiver);
    string msgs_str = "";
    for(int i=0; i<msgs.size(); i++){
        Msg msg = deserialize(msgs[i]);

        std::tm* timePtr = std::localtime(&msg.timestamp);
        ostringstream oss;
        oss << std::put_time(timePtr, "%b %d %H:%M");
        string timestamp = oss.str();

        msgs_str += msg.sender + "|" + msg.content + "|" + timestamp + "\n";
    }
    Msg msgsList;
    msgsList.type = MsgType::GET_MSGS;
    msgsList.sender = sender;
    msgsList.receiver = receiver;
    msgsList.content = msgs_str;
    sendMsg(msgsList, socket);
}
