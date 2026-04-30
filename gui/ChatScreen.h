#pragma once

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QStackedWidget>

#include "../server/ClientSession.h"

#include <string>
using namespace std;

class ChatScreen : public QWidget {
    public:
        ChatScreen(QStackedWidget* parent, ClientSession* cli);
    private:
        ClientSession* client;
        QVBoxLayout *layout;
        QTabWidget *tabs;
        QListWidget *usersList;
        QListWidget *chat;
        QWidget *chatsPage;
        QHBoxLayout *chatsLayout;
        QWidget *chattingPart;
        QVBoxLayout *chattingPartLayout;
        QLineEdit *msgInput;
        QPushButton *sendMsgBtn;
        QWidget *logoutPage;
        QVBoxLayout *logoutLayout;
        QPushButton *logoutBtn;
        string currentChat;
};
