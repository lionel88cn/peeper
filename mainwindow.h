#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "logindialog.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <QTreeView>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <qdebug.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QMenu *mainMenu;
    QAction *openAct;
    QAction *connectAct;
    QAction *closeAct;
    QAction *aboutAct;
    QTreeView *friendTreeView;
    QStandardItemModel *friendTreeModel;
    int login();
    void setUpGUI();
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void selectionChangedSlot(const QItemSelection &, const QItemSelection &);
};

#endif // MAINWINDOW_H
