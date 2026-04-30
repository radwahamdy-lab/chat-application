#pragma once

#include "LoginScreen.h"
#include "../server/ClientSession.h"
#include "../common/Message.h"
#include "../common/Serializer.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <string>
#include <iostream>
using namespace std;

class LoginScreen : public QWidget {
    public:
        LoginScreen(QStackedWidget* parent, ClientSession* cli);
        void onLoginClicked(QStackedWidget* parent);
        bool isLoggedIn(Msg msg, string usrname);
    private:
        QLineEdit *usernameEdit;
        QLineEdit *emailEdit;
        QLineEdit *passwordEdit;
        QPushButton *loginBtn;
        QPushButton *backBtn;
        QPushButton *togglePassBtn;
        QHBoxLayout *passwordLayout;
        QWidget *passwordField;
        ClientSession *client;
        bool isPassVisible = false;
};
