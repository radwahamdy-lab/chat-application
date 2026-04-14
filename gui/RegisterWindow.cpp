#include "RegisterWindow.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QRegularExpression>
#include <QLabel>

RegisterWindow::RegisterWindow(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Register");
    title->setAlignment(Qt::AlignCenter);

  nameEdit = new QLineEdit;
    nameEdit->setPlaceholderText("Full Name");

    emailEdit = new QLineEdit;
    emailEdit->setPlaceholderText("Email");

    usernameEdit = new QLineEdit;
    usernameEdit->setPlaceholderText("Username");

    passwordEdit = new QLineEdit;
    passwordEdit->setPlaceholderText("Password");
    registerButton = new QPushButton("Register");

    layout->addWidget(title);
    layout->addWidget(nameEdit);
    layout->addWidget(emailEdit);
    layout->addWidget(usernameEdit);
    layout->addWidget(passwordEdit);
    layout->addWidget(registerButton);

    connect(registerButton, &QPushButton::clicked,
            this, &RegisterWindow::onRegisterClicked);
}

void RegisterWindow::onRegisterClicked()
{
    QString name = nameEdit->text().trimmed();
    QString email = emailEdit->text().trimmed();
    QString username = usernameEdit->text().trimmed();
    QString password = passwordEdit->text().trimmed();

    
    if (name.isEmpty() || email.isEmpty() ||
        username.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Error",
                             "Please fill in all fields.");
        return;
    }

    
    if (!isValidEmail(email))
    {
        QMessageBox::warning(this, "Error",
                             "Invalid email format.");
        return;
    }

    
    QMessageBox::information(this, "Success",
                             "Registration successful!");
}

bool RegisterWindow::isValidEmail(const QString &email)
{
    QRegularExpression regex(
        "^[\\w\\.-]+@[\\w\\.-]+\\.[a-zA-Z]{2,}$"
    );

    return regex.match(email).hasMatch();
}