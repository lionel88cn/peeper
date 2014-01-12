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
    QStandardItem *americaItem = new QStandardItem("America");
    QStandardItem *mexicoItem =  new QStandardItem("Canada");
    QStandardItem *usaItem =     new QStandardItem("USA");
    QStandardItem *bostonItem =  new QStandardItem("Boston");
    QStandardItem *europeItem =  new QStandardItem("Europe");
    QStandardItem *italyItem =   new QStandardItem("Italy");
    QStandardItem *romeItem =    new QStandardItem("Rome");
    QStandardItem *veronaItem =  new QStandardItem("Verona");

    //building up the hierarchy
    rootNode->    appendRow(americaItem);
    rootNode->    appendRow(europeItem);
    americaItem-> appendRow(mexicoItem);
    americaItem-> appendRow(usaItem);
    usaItem->     appendRow(bostonItem);
    europeItem->  appendRow(italyItem);
    italyItem->   appendRow(romeItem);
    italyItem->   appendRow(veronaItem);

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
