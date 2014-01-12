#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "logindialog.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <qdebug.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    int login();
    void setUpGUI();
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
};

#endif // MAINWINDOW_H
