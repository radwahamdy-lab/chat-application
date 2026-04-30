#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QStackedWidget>

#include "../server/ClientSession.h"

class SignupScreen : public QWidget {
    public:
        SignupScreen(QStackedWidget* parent, ClientSession* cli);
        void OnSignupClicked();
    private:
        QLineEdit *usernameEdit;
        QLineEdit *emailEdit;
        QLineEdit *passwordEdit;
        QPushButton *signupBtn;
        QPushButton *backBtn;
        QPushButton *togglePassBtn;
        QHBoxLayout *passwordLayout;
        QWidget *passwordField;
        ClientSession* client;
        bool isPassVisible = false;

};
