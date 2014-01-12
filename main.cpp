#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;
    LoginDialog* loginDialog = new LoginDialog();
    //loginDialog->setUsername( "Luca" );  // optional
    //connect(loginDialog,SIGNAL(acceptLogin(QString&,QString&,int&)),this,SLOT(slotAcceptUserLogin(QString&,QString&)));
    loginDialog->exec();
    mainWindow.show();
    return a.exec();
}
