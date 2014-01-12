#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QStringList>
#include <QDebug>

class LoginDialog : public QDialog
{
    Q_OBJECT
private:
    QLabel* labelUsername;
    QLabel* labelPassword;
    QDialogButtonBox* buttons;
    void setUpGUI();
public:
    enum LoginCode{Successful,Failed,Closed};
    QComboBox* comboUsername;
    QLineEdit* editPassword;
    explicit LoginDialog(QWidget *parent = 0);
    static int getCredentials(QString& username,QString& password);
    void setUsername(QString& username);
    void setPassword(QString& password);
    void setUsernamesList(const QStringList& usernames);
};

#endif // LOGINDIALOG_H
