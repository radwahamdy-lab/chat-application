#include "MainScreen.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QStackedWidget>

MainScreen::MainScreen(QStackedWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    loginBtn = new QPushButton("Login");
    signupBtn = new QPushButton("Sign Up");

    layout->addWidget(loginBtn);
    layout->addWidget(signupBtn);

    connect(loginBtn, &QPushButton::clicked, this, [parent](){
        parent->setCurrentIndex(1);
    }, Qt::QueuedConnection);

    connect(signupBtn, &QPushButton::clicked, this, [parent](){
        parent->setCurrentIndex(2);
    }, Qt::QueuedConnection);
}
