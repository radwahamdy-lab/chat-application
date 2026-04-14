#include "LoginWindow.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QRegularExpression>
#include <QLabel>

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Login");
    title->setAlignment(Qt::AlignCenter);

    usernameEdit = new QLineEdit;
    usernameEdit->setPlaceholderText("Username");

    emailEdit = new QLineEdit;
    emailEdit->setPlaceholderText("Email");

    passwordEdit = new QLineEdit;
    passwordEdit->setPlaceholderText("Password");

    loginButton = new QPushButton("Login");

    layout->addWidget(title);
    layout->addWidget(usernameEdit);
    layout->addWidget(emailEdit);
    layout->addWidget(passwordEdit);
    layout->addWidget(loginButton);

    connect(loginButton, &QPushButton::clicked,
            this, &LoginWindow::onLoginClicked);
}

void LoginWindow::onLoginClicked()
{
    try {
        QString username = usernameEdit->text().trimmed();
        QString email = emailEdit->text().trimmed();
        QString password = passwordEdit->text().trimmed();

        
        if (username.isEmpty() || email.isEmpty() || password.isEmpty())
            throw std::runtime_error("Please fill in all fields.");

        
        if (!isValidEmail(email))
            throw std::invalid_argument("Invalid email format.");

        
        checkEmailExists(email);

        
        checkCredentials(username, email, password);

        QMessageBox::information(this, "Success",
                                 "Login successful!");
    }
    catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Input Error", e.what());
    }
    catch (const std::runtime_error &e) {
        QMessageBox::warning(this, "Error", e.what());
    }
    catch (const std::exception &e) {
        QMessageBox::critical(this, "System Error", e.what());
    }
}

bool LoginWindow::isValidEmail(const QString &email)
{
    QRegularExpression regex(
        "^[\\w\\.-]+@[\\w\\.-]+\\.[a-zA-Z]{2,}$"
    );
    return regex.match(email).hasMatch();
}

/*
   
*/

void LoginWindow::checkEmailExists(const QString &email)
{
    
    if (email != "test@example.com") {
        throw std::runtime_error("Email does not exist.");
    }
}

void LoginWindow::checkCredentials(const QString &username,
                                   const QString &email,
                                   const QString &password)
{
    
    if (username != "user" || password != "1234") {
        throw std::runtime_error("Incorrect username or password.");
    }
}