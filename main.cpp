#include <string>
using namespace std;

#include <QApplication>
#include <QStackedWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QObject>
#include "gui/LoginScreen.h"
#include "gui/MainScreen.h"
#include "gui/SignupScreen.h"
#include "gui/ChatScreen.h"
#include "server/ChatServer.h"
#include "server/ClientSession.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    string filename = "database/users_db.txt"; 
    int port = 1234;
    ChatServer* chatserver = new ChatServer(filename, port);

    std::thread([chatserver]() {
        chatserver->run();
    }).detach();

    ClientSession *client = new ClientSession(port);

    QMainWindow w;
    w.setWindowTitle("Chat Application");
    w.resize(500, 400);

    QWidget *centralWidget = new QWidget(&w);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QStackedWidget *stackedWidget = new QStackedWidget;

    MainScreen mainPage(stackedWidget);
    SignupScreen signupPage(stackedWidget, client);
    LoginScreen loginPage(stackedWidget, client);

    ChatScreen chatPage(stackedWidget, client);

    // Add Views to Stacked Widget
    stackedWidget->addWidget(&mainPage);
    stackedWidget->addWidget(&loginPage);
    stackedWidget->addWidget(&signupPage);
    stackedWidget->addWidget(&chatPage);

    // Display main page
    stackedWidget->setCurrentIndex(0);
    
    mainLayout->addWidget(stackedWidget);
    w.setCentralWidget(centralWidget);
    w.show();

    return a.exec();
}