#include "RegisterWindow.h"
#include <QMessageBox>

RegisterWindow::RegisterWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::RegisterWindow) {
    ui->setupUi(this);
}

RegisterWindow::~RegisterWindow() {
    delete ui;
}

void RegisterWindow::on_registerButton_clicked() {
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();
    QString confirm = ui->confirmPasswordInput->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all fields");
        return;
    }

    if (password != confirm) {
        QMessageBox::warning(this, "Error", "Passwords do not match");
        return;
    }

    emit registerRequested(username, password);
}