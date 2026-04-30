#include "SignupScreen.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QStackedWidget>
#include "../server/ClientSession.h"
#include <string>
#include <iostream>
using namespace std;

SignupScreen::SignupScreen(QStackedWidget *parent, ClientSession* cli) : QWidget(parent), client(cli) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Sign Up");
    title->setAlignment(Qt::AlignCenter);

    usernameEdit = new QLineEdit;
    usernameEdit->setPlaceholderText("Username (5-10 characters)");

    emailEdit = new QLineEdit;
    emailEdit->setPlaceholderText("Email (10-20 characters)");

    passwordField = new QWidget(this);
    passwordLayout = new QHBoxLayout(passwordField);
    passwordEdit = new QLineEdit;
    passwordEdit->setPlaceholderText("Password (8-10 characters)");
    passwordEdit->setEchoMode(QLineEdit::Password);
    togglePassBtn = new QPushButton("Show");
    passwordLayout->addWidget(passwordEdit, 3);
    passwordLayout->addWidget(togglePassBtn, 1);
    passwordField->setContentsMargins(0, 0, 0, 0);
    passwordLayout->setContentsMargins(0, 0, 0, 0);
    passwordField->setLayout(passwordLayout);


    signupBtn = new QPushButton("Sign Up");
    backBtn = new QPushButton("Back");
    
    layout->addStretch();
    layout->addWidget(title);
    layout->addStretch();
    layout->addWidget(usernameEdit);
    layout->addWidget(emailEdit);
    layout->addWidget(passwordField);
    layout->addWidget(signupBtn);
    layout->addWidget(backBtn);

    QObject::connect(signupBtn, &QPushButton::clicked, this, &SignupScreen::OnSignupClicked, Qt::QueuedConnection);

    QObject::connect(backBtn, &QPushButton::clicked, this, [parent](){
        parent->setCurrentIndex(0);
    }, Qt::QueuedConnection);

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

    QObject::connect(client, &ClientSession::signupUpdateReceived, this, [this, parent](bool status){
        QMessageBox *msgBox = new QMessageBox();
        msgBox->setWindowTitle("Sign Up Update");
        if(status)
            msgBox->setText("Sign Up was Successful. You can now Log in.");
        else
            msgBox->setText("Sign up failed. Please try again.");
        msgBox->exec();
        parent->setCurrentIndex(1);
    }, Qt::QueuedConnection);
}

void SignupScreen::OnSignupClicked(){
    string usrname = usernameEdit->text().toStdString();
    string email = emailEdit->text().toStdString();
    string password = passwordEdit->text().toStdString();

    if((usrname.length() < 5 || usrname.length() > 10) || (email.length() < 10 || email.length() > 20) || (password.length() < 8 || password.length() > 10)){
        QMessageBox* message = new QMessageBox;
        message->setWindowTitle("Warning");
        message->setText("Please follow requirements for each field.");
        message->exec();
        return;
    }

    client->sendSignUpRequest(usrname, email, password);
}
