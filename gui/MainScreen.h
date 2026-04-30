#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>

class MainScreen : public QWidget {
    public:
        MainScreen(QStackedWidget* parent);
    private:
        QPushButton *loginBtn;
        QPushButton *signupBtn;
};
