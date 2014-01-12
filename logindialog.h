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
    QComboBox* comboUsername;
    QLineEdit* editPassword;
    QDialogButtonBox* buttons;
    void setUpGUI();
public:
    explicit LoginDialog(QWidget *parent = 0);
    void setUsername(QString& username);
    void setPassword(QString& password);
    void setUsernamesList(const QStringList& usernames);
signals:
    void acceptLogin(QString& username,QString& password,int& indexNumber);

public slots:
    void slotAcceptLogin();

};

#endif // LOGINDIALOG_H
