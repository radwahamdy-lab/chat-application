#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <QObject>
#include "../common/Message.h"
#include "../common/Serializer.h"

using boost::asio::ip::tcp;


Q_DECLARE_METATYPE(Msg)


class ClientSession : public QObject{
    Q_OBJECT
    
    public:
        ClientSession(int port);
        void getMsg();
        void sendMsg(Msg msg);
        void sendLoginRequest(string, string, string);
        void checkForLogin(Msg);
        bool checkForSignup(Msg msg);
        void sendSignUpRequest(string, string, string);
        void getAllUsers();
        void getMsgsForChat(string, string);
        string getUsername();
        void handleErrors(Msg);
        void disconnect();
        void logout();
    private:
        boost::asio::io_context io;
        tcp::socket* socket = new tcp::socket(io);
        string username;
        bool loggedIn;
    signals:
        void msgReceived(Msg msg);
        void loginUpdateReceived(bool status);
        void signupUpdateReceived(bool);
        void usersListReceived(Msg msg);
        void msgsListReceived(QString, QString);
        void receiverNotFound(string);
        
};