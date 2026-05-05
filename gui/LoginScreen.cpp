#include "LoginScreen.h"
#include "../server/ClientSession.h"
#include "../common/Message.h"
#include "../common/Serializer.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QMessageBox>
#include <string>
#include <iostream>
using namespace std;


LoginScreen::LoginScreen(QStackedWidget *parent, ClientSession* cli) : QWidget(parent), client(cli){

    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *title = new QLabel("Login");
    title->setAlignment(Qt::AlignCenter);

    usernameEdit = new QLineEdit;
    usernameEdit->setPlaceholderText("Username");

    emailEdit = new QLineEdit;
    emailEdit->setPlaceholderText("Email");

    passwordField = new QWidget();
    passwordLayout = new QHBoxLayout(passwordField);
    passwordEdit = new QLineEdit;
    passwordEdit->setPlaceholderText("Password");
    passwordEdit->setEchoMode(QLineEdit::Password);
    togglePassBtn = new QPushButton("Show");
    passwordLayout->addWidget(passwordEdit, 3);
    passwordLayout->addWidget(togglePassBtn, 1);
    passwordField->setContentsMargins(0, 0, 0, 0);
    passwordLayout->setContentsMargins(0, 0, 0, 0);
    passwordField->setLayout(passwordLayout);

    loginBtn = new QPushButton("Login");
    backBtn = new QPushButton("Back");

    layout->addStretch();
    layout->addWidget(title);
    layout->addStretch();
    layout->addWidget(usernameEdit);
    layout->addWidget(emailEdit);
    layout->addWidget(passwordField);
    layout->addWidget(loginBtn);
    layout->addWidget(backBtn);

    QObject::connect(backBtn, &QPushButton::clicked, this, [parent](){parent->setCurrentIndex(0);}, Qt::QueuedConnection);
    QObject::connect(loginBtn, &QPushButton::clicked, this, [parent, this](){onLoginClicked(parent);}, Qt::QueuedConnection);
    QObject::connect(togglePassBtn, &QPushButton::clicked, this, [this](){
        if(isPassVisible) {
            passwordEdit->setEchoMode(QLineEdit::Password);
            togglePassBtn->setText("Show");
        }
        else {
            passwordEdit->setEchoMode(QLineEdit::Normal);
            togglePassBtn->setText("Hide");
        }
        isPassVisible = !isPassVisible;
    }, Qt::QueuedConnection);
}

void LoginScreen::onLoginClicked(QStackedWidget* parent){
    string usrname = usernameEdit->text().toStdString();
    string email = emailEdit->text().toStdString();
    string password = passwordEdit->text().toStdString();

    client->sendLoginRequest(usrname, email, password);

    QObject::connect(client, &ClientSession::loginUpdateReceived, this, [this, usrname, parent](bool status){
        QMessageBox* message = new QMessageBox;
        message->setWindowTitle("Login Update");
        if (status){
            usernameEdit->clear();
            emailEdit->clear();
            passwordEdit->clear();
            parent->setCurrentIndex(3);
            message->setText("Login was successful. You can now chat!");
        } else 
            message->setText("Login failed. Try again.");
        message->exec();
    }, Qt::QueuedConnection);

}
