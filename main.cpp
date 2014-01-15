#include "mainwindow.h"
#include "findWindowList.h"
#include "Bot.h"
#include <QApplication>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    findWindowList();
    Bot b;
	mybuddylist.readLog();
	MainWindow w;
	w.setBot(&b);
    w.show();

    return a.exec();
}
