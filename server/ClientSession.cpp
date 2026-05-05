#include <boost/asio.hpp>
using boost::asio::ip::tcp;

#include <iostream>
#include <QObject>
#include "../common/Message.h"
#include "../common/Serializer.h"
#include <bcrypt/BCrypt.hpp>
#include "ClientSession.h"
#include <QMetaType>
#include <regex>
#include <string>
#include <sstream>
using namespace std;
// Send msgs from usr to server
// Receive msgs from server to user

ClientSession::ClientSession(int port){
    qRegisterMetaType<Msg>("Msg");
    tcp::resolver resolver(io);
    tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", to_string(port));
    boost::asio::connect(*socket, endpoints);
    getMsg();
    std::thread([this]() {
        io.run();
    }).detach();
}

void ClientSession::getMsg(){
    char* buf = new char[1024];
    socket->async_read_some(boost::asio::buffer(buf, 1024), [this, buf](boost::system::error_code ec, size_t len){
        
        if (!ec) {
            string msgs_str(buf, len);
            stringstream ss(msgs_str);
            string msg_str;
            cout << msgs_str << endl;
            while(getline(ss, msg_str, '}')){
                msg_str += '}';
                cout << "msg received by client: " << msg_str << endl;
                if(msg_str == "") return;
                Msg msg = deserialize(msg_str);
                
                if(msg.type == MsgType::LOGIN){
                    checkForLogin(msg);
                    emit loginUpdateReceived(loggedIn);
                } else if(msg.type == MsgType::REGISTER){
                    bool isSignedIn = checkForSignup(msg);
                    emit signupUpdateReceived(isSignedIn);
                } else if(msg.type == MsgType::GET_USERS){
                    emit usersListReceived(msg);
                } else if(msg.type == MsgType::GET_MSGS){
                    emit msgsListReceived(QString::fromStdString(msg.content), QString::fromStdString(msg.receiver));
                } else if(msg.type == MsgType::CHAT){
                    emit msgReceived(msg);
                } else if(msg.type == MsgType::STATUS){
                    if(msg.sender != username)
                        getAllUsers();
                } else if(msg.type == MsgType::ERR){
                    handleErrors(msg);
                }
            }
            delete[] buf;
            getMsg();
        } else {
            if(ec != boost::asio::error::eof)
                cout << "Read error: " << ec.message() << endl;
            delete[] buf;
        }
    });
}

void ClientSession::sendMsg(Msg msg){
    string msg_str = serialize(msg);
    boost::asio::async_write(*socket, boost::asio::buffer(msg_str), [msg, this](boost::system::error_code ec, size_t len){
        if(msg.type == MsgType::LOGOUT)
            if (socket && socket->is_open())
                socket->cancel();
        getMsg();
    });
}

void ClientSession::sendLoginRequest(string usrname, string email, string password){
    Msg credentials;
    credentials.type = MsgType::LOGIN;
    credentials.sender = usrname;
    credentials.receiver = "server";
    credentials.content = usrname + "," + email + "," + password;
    username = usrname;
    sendMsg(credentials);
}

void ClientSession::checkForLogin(Msg msg){
    if(msg.receiver == username){
        if(msg.content == "login successful")
            loggedIn = true;
        else if(msg.content == "login unsuccessful")
            loggedIn = false;
    }
}

bool ClientSession::checkForSignup(Msg msg){
    bool status;
    if(msg.receiver == username){
        if(msg.content == "sign up successful")
            status = true;
        else if(msg.content == "sign up unsuccessful")
            status = false;
    }
    return status;
}

void ClientSession::sendSignUpRequest(string usrname, string email, string password){
    Msg credentials;
    credentials.type = MsgType::REGISTER;
    credentials.sender = usrname;
    credentials.receiver = "server";
    credentials.content = usrname + "," + email + "," + BCrypt::generateHash(password);
    username = usrname;
    sendMsg(credentials);
}

void ClientSession::getAllUsers(){
    Msg msg;
    msg.type = MsgType::GET_USERS;
    msg.sender = username;
    msg.receiver = "server";
    msg.content = "all users";
    sendMsg(msg);
}


void ClientSession::getMsgsForChat(string sender, string receiver){
    Msg msg;
    msg.type = MsgType::GET_MSGS;
    msg.sender = sender;
    msg.receiver = "server";
    msg.content = receiver;
    sendMsg(msg);
}


string ClientSession::getUsername(){
    return username;
}

void ClientSession::handleErrors(Msg error){
    regex pattern(".*cannot be found$");

    if (regex_match(error.content, pattern)) {
        stringstream ss(error.content);
        string receiver;
        ss >> receiver;
        emit receiverNotFound(receiver);
    }
}

void ClientSession::logout(){
    Msg logoutMsg;
    logoutMsg.type = MsgType::LOGOUT;
    logoutMsg.sender = username;
    logoutMsg.receiver = "server";
    logoutMsg.content = "";
    sendMsg(logoutMsg);
}

void ClientSession::disconnect(){
    logout();
    loggedIn = false;
    username.clear();
}