#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    int retCode;
    while(1){
        retCode=login();
        if(retCode==LoginDialog::Closed||retCode==LoginDialog::Successful) break;
    }
    if(retCode==LoginDialog::Closed) QTimer::singleShot(0, this, SLOT(close()));
    setUpGUI();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setUpGUI()
{

}

int MainWindow::login(){
    int dialogRetCode;
    QString username,password;
    dialogRetCode=LoginDialog::getCredentials(username,password);
    qDebug()<<"username: "<<username<<"password: "<<password;
    if(dialogRetCode==QDialog::Rejected) return LoginDialog::Closed;
    if(username=="fuck"&&password=="fuck") return LoginDialog::Successful;
    return LoginDialog::Failed;
}
