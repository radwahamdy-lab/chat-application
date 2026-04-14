#pragma once
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class RegisterWindow; }
QT_END_NAMESPACE

class RegisterWindow : public QWidget {
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();

signals:
    void registerRequested(const QString& username, const QString& password);

private slots:
    void on_registerButton_clicked();

private:
    Ui::RegisterWindow *ui;
};