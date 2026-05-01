#include "ChatScreen.h"
#include <QTabWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QString>
#include "../server/ClientSession.h"
#include "../database/User.h"
#include "../common/Serializer.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
using namespace std;

ChatScreen::ChatScreen(QStackedWidget *parent, ClientSession* cli) : QWidget(parent), client(cli) {
    layout = new QVBoxLayout(this);
    tabs = new QTabWidget();

    // Chats Tab setup
    chatsPage = new QWidget();
    chatsLayout = new QHBoxLayout(chatsPage);
    usersList = new QListWidget(chatsPage);

    chattingPart = new QWidget();
    chattingPartLayout = new QVBoxLayout(chattingPart);
    tabs->addTab(chatsPage, "Chats");
    chatsLayout->addWidget(usersList, 1);
    chatsLayout->addWidget(chattingPart, 3);
    chatsPage->setLayout(chatsLayout);

    // Logout Tab Setup
    logoutPage = new QWidget();
    logoutLayout = new QVBoxLayout(logoutPage);
    logoutBtn = new QPushButton("Logout");
    logoutLayout->addWidget(logoutBtn);
    logoutPage->setLayout(logoutLayout);
    tabs->addTab(logoutPage, "Logout");

    // Chatting Part setup
    chat = new QListWidget();
    msgInput = new QLineEdit;
    msgInput->setPlaceholderText("Type Your Message.");
    sendMsgBtn = new QPushButton("Send");
    sendMsgBtn->setEnabled(false);
    chattingPartLayout->addWidget(chat);
    chattingPartLayout->addWidget(msgInput);
    chattingPartLayout->addWidget(sendMsgBtn);
    chattingPart->setLayout(chattingPartLayout);
    
    layout->addWidget(tabs);

    QObject::connect(logoutBtn, &QPushButton::clicked, this, [this, parent](){
        client->disconnect();
        parent->setCurrentIndex(0);
        tabs->setCurrentIndex(0);
    }, Qt::QueuedConnection);
    
    QObject::connect(parent, &QStackedWidget::currentChanged, this, [this](int index){
        if(index == 3)
            client->getAllUsers();
    }, Qt::QueuedConnection);

    QObject::connect(client, &ClientSession::usersListReceived, this, [this](Msg usersListMsg){
        usersList->clear();
        stringstream ss(usersListMsg.content);
        string allUsers;
        string activeUsers;
        getline(ss, allUsers);
        getline(ss, activeUsers);
        stringstream as(allUsers);
        string user;
        while(getline(as, user, ',')){
            if(user != client->getUsername()){
                string item;
                size_t index = activeUsers.find(user);
                if(index != std::string::npos && activeUsers[index-1] == ',' && activeUsers[index+user.length()] == ',')
                    item = user + " (online)";
                else
                    item = user + " (offline)";
                usersList->addItem(QString::fromStdString(item));
            }   
        }
    }, Qt::QueuedConnection);

    QObject::connect(usersList, &QListWidget::itemClicked, this, [this](QListWidgetItem* item){
        msgInput->clear();
        stringstream ss(item->text().toStdString());
        string otherUser;
        ss >> otherUser;
        client->getMsgsForChat(client->getUsername(), otherUser);
        currentChat = otherUser;
    }, Qt::QueuedConnection);
    

    QObject::connect(client, &ClientSession::msgsListReceived, this, [this](QString content, QString username){
        chat->clear();
        stringstream ss(content.toStdString());
        string sender;
        string msg;
        string timestamp;
        if(content.isEmpty()) {
            sendMsgBtn->setEnabled(true);
            return;
        }
            
        while (getline(ss, sender, '|') && getline(ss, msg, '|') && getline(ss, timestamp)){
            string msgItem = sender + " (" + timestamp + "): " + msg;
            chat->addItem(QString::fromStdString(msgItem));
        }
        sendMsgBtn->setEnabled(true);
    }, Qt::QueuedConnection);

    QObject::connect(sendMsgBtn, &QPushButton::clicked, this, [this](){
        if(!msgInput->text().isEmpty()){
            Msg msg;
            msg.type = MsgType::CHAT;
            msg.sender = client->getUsername();
            msg.receiver = currentChat;
            msg.content = msgInput->text().toStdString();
            client->sendMsg(msg);
            client->getMsgsForChat(client->getUsername(), currentChat);
            msgInput->clear();
        } else {
            QMessageBox* message = new QMessageBox;
            message->setWindowTitle("Warning");
            message->setText("Please enter a message to be able to send.");
            message->exec();
        }
    }, Qt::QueuedConnection);

    QObject::connect(client, &ClientSession::receiverNotFound, this, [this](string receiver){
        QMessageBox* message = new QMessageBox;
        message->setWindowTitle("Warning");
        string msg = receiver + " cannot be found.";
        message->setText(QString::fromStdString(msg));
        message->exec();
    }, Qt::QueuedConnection);

    QObject::connect(client, &ClientSession::msgReceived, this, [this](Msg msg){
        if(msg.sender == currentChat){
            client->getMsgsForChat(client->getUsername(), currentChat);
        }
    }, Qt::QueuedConnection);

}


