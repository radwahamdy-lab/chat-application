#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <stdexcept>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);

private slots:
    void onLoginClicked();

private:
    bool isValidEmail(const QString &email);

    // Simulated DB functions (will throw exceptions)
    void checkEmailExists(const QString &email);
    void checkCredentials(const QString &username,
                          const QString &email,
                          const QString &password);

    QLineEdit *usernameEdit;
    QLineEdit *emailEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
};

#endif 