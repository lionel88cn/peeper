#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logindialog.h"
#include <QMessageBox>
#include <QTimer>
#include <QTreeView>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <qdebug.h>
#include "Bot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
	void setBot(Bot* b);
    ~MainWindow();

	void selectionChangedSlot(const QItemSelection &, const QItemSelection &);

private:
	int timerId;
	Bot* msgBot;

	QMenu *mainMenu;
    QAction *openAct;
    QAction *connectAct;
    QAction *closeAct;
    QAction *aboutAct;
    QTreeView *friendTreeView;
    QStandardItemModel *friendTreeModel;
    int login();
    void setUpGUI();

protected:
    void timerEvent(QTimerEvent *event);
};

#endif // MAINWINDOW_H
