#include "mainwindow.h"
#include "findWindowList.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    int retCode;
    while(1)
	{
        retCode=login();
        if(retCode==LoginDialog::Closed||retCode==LoginDialog::Successful)
		{
			break;
		}
    }
    if(retCode==LoginDialog::Closed)
	{
		QTimer::singleShot(0, this, SLOT(close()));
	}
    setUpGUI();

	timerId = startTimer(1000);
}

void MainWindow::setBot(Bot* b)
{
	msgBot=b;
}

MainWindow::~MainWindow()
{
	killTimer(timerId);
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    //qDebug() << "timerEvent";
	msgBot->receiveMsg();
	friendTreeModel->clear();

	if (mybuddylist.head!=mybuddylist.rear)
    {
        QStandardItem *rootNode = friendTreeModel->invisibleRootItem();
		BuddyNode* p=mybuddylist.head;
        while (1)
        {
			QStandardItem *onebuddyjiditem = new QStandardItem(QString::fromStdString(p->buddyJID));
			rootNode->appendRow(onebuddyjiditem);
            for (int i=0;i<p->onebuddywindowlist.win_num;i++)
            {
                QStandardItem *onewindowitem = new QStandardItem(QString::fromStdString(p->onebuddywindowlist.content[i]));
				onebuddyjiditem->appendRow(onewindowitem);
            }
            if (!p->next)
            {
                break;
            }
            else
            {
                p=p->next;
            }
        }
    }
	friendTreeView->expandAll();
}

void MainWindow::setUpGUI()
{
    openAct=new QAction("&Open",this);
    connectAct=new QAction("&Connect",this);
    aboutAct=new QAction("&Info",this);
    closeAct=new QAction("&Close",this);
    mainMenu=menuBar()->addMenu("&Main");
    mainMenu->addAction(openAct);
    mainMenu->addAction(connectAct);
    mainMenu->addAction(aboutAct);
    mainMenu->addAction(closeAct);

    friendTreeView = new QTreeView(this);
    setCentralWidget(friendTreeView);
    friendTreeModel = new QStandardItemModel ;
    QStandardItem *rootNode = friendTreeModel->invisibleRootItem();

    //defining a couple of items
	if (mybuddylist.head!=mybuddylist.rear)
    {
        BuddyNode* p=mybuddylist.head;
        while (1)
        {
            QStandardItem *onebuddyjiditem = new QStandardItem(QString::fromStdString(p->buddyJID));
			rootNode->appendRow(onebuddyjiditem);
            if (!p->next)
            {
                break;
            }
            else
            {
                p=p->next;
            }
        }
    }

    //register the model
    friendTreeView->setModel(friendTreeModel);
    friendTreeView->expandAll();

    //selection changes shall trigger a slot
    QItemSelectionModel *selectionModel= friendTreeView->selectionModel();
    connect(selectionModel, SIGNAL(selectionChanged (const QItemSelection &, const QItemSelection &)),
            this, SLOT(selectionChangedSlot(const QItemSelection &, const QItemSelection &)));
}

void MainWindow::selectionChangedSlot(const QItemSelection &, const QItemSelection &){
    //get the text of the selected item
    const QModelIndex index = friendTreeView->selectionModel()->currentIndex();
    QString selectedText = index.data(Qt::DisplayRole).toString();
    //find out the hierarchy level of the selected item
    int hierarchyLevel=1;
    QModelIndex seekRoot = index;
    while(seekRoot.parent() != QModelIndex())
    {
        seekRoot = seekRoot.parent();
        hierarchyLevel++;
    }
    QString showString = QString("%1, Level %2").arg(selectedText)
                         .arg(hierarchyLevel);
    setWindowTitle(showString);
}

int MainWindow::login(){
    int dialogRetCode;
    QString username,password;
//    QMessageBox::information(this,tr("fuck"),tr("fuck"));
    dialogRetCode=LoginDialog::getCredentials(username,password);
    qDebug()<<"username: "<<username<<"password: "<<password;
    if(dialogRetCode==QDialog::Rejected) return LoginDialog::Closed;
    if(username=="fuck"&&password=="fuck") return LoginDialog::Successful;
    return LoginDialog::Failed;
}