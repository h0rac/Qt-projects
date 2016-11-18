#include "windows/mainwindow.h"
#include "ui_mainwindow.h"
#include "gscene.h"
#include <QListWidgetItem>
#include <QIcon>
#include <QPixmap>
#include <QSize>
#include <iostream>
#include <QString>
#include <QtDebug>
#include <gui/gnetdevice.h>
#include <windows/stpwindow.h>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QSplitter>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    pscene = new GScene(this);
    pscene->getMainWindow(this);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setScene(pscene);
    ui->graphicsView->show();
    this->setToolList();
    this->setItemList();
    this->setProtoList();

    status = false;

    connect(ui->actionExit,&QAction::triggered,this,&MainWindow::close);
    connect(ui->actionStart,&QAction::triggered,this,&MainWindow::startClicked);
    connect(ui->actionStop,&QAction::triggered,this,&MainWindow::stopClicked);
    connect(ui->actionPause,&QAction::triggered,this,&MainWindow::pauseClicked);
    connect(ui->actionStepForward,&QAction::triggered,this,&MainWindow::stepForwardClicked);
    connect(ui->actionStepBackward,&QAction::triggered,this,&MainWindow::stepBackwardClicked);
    connect(ui->toolList,&QListWidget::itemClicked,this,&MainWindow::getToolList);
    connect(ui->itemList,&QListWidget::itemClicked,this,&MainWindow::getItemList);
    connect(ui->protoList,&QListWidget::itemDoubleClicked,this,&MainWindow::setProtoWindow);
    //connect(pscene->getActDevModel(),&QStandardItemModel::itemChanged,this,&MainWindow::testModel);

}


void MainWindow::setToolList()
{
    QListWidgetItem * conn = new QListWidgetItem(QIcon(QPixmap(":/connect.ico")),"Connect");
    QListWidgetItem * select = new QListWidgetItem(QIcon(QPixmap(":/select.ico")),"Select");
    ui->toolList->addItem(conn);
    ui->toolList->addItem(select);
    ui->toolList->setIconSize(QSize(35,35));

}

void MainWindow::setItemList()
{
    QListWidgetItem * router = new QListWidgetItem(QIcon(QPixmap(":/router.jpg")),"Router");
    QListWidgetItem * sw = new QListWidgetItem(QIcon(QPixmap(":/switch.jpg")),"Switch");
    ui->itemList->addItem(router);
    ui->itemList->addItem(sw);
    ui->itemList->setIconSize(QSize(40,40));
}
void MainWindow::setProtoList()
{
    protocols <<"STP"<<"MPLS";
    ui->protoList->addItems(protocols);

}



void MainWindow::getToolList()
{
    QString item = ui->toolList->currentItem()->text();
    std::cout<<"Current item"<<std::endl;
    if (item == "Connect" || item == "Select")
    {
        pscene->setChoice(item);
        qDebug()<<"choice in getToolList"<<pscene->getChoice();
    }
}
void MainWindow::getItemList()
{
    QString item = ui->itemList->currentItem()->text();
    std::cout<<"Current item"<<std::endl;
    if (item == "Router" || item == "Switch")
    {
      pscene->setChoice(item);
      qDebug()<<"choice in getItemList"<<pscene->getChoice();
    }
}
void MainWindow::setProtoWindow()
{

    StpWindow *stpwindow = new StpWindow();
    QString item = ui->protoList->currentItem()->text();
    qDebug()<<"Selected item"<<item;
    if (item == "STP")
    {
        stpwindow->setWindowTitle("STP Protocol");
        QStandardItemModel *tmodel = pscene->getActDevModel();
        QListView * vtemp = stpwindow->setSTPactDevView();
        vtemp->setModel(tmodel);
        stpwindow->setStpModel(tmodel);
        stpwindow->show();

    }
    else
    {
        qDebug("Other windows not implemented");
    }

}

QListView * MainWindow::getActDevListView()
{
    return ui->actDevList;
}

void MainWindow::startClicked()
{
    status = pscene->coreInterface->tellSysManagerStart();
    if(status == true)
    {
        ui->actionStart->setDisabled(true);
        ui->actionPause->setDisabled(false);
    }
}

void MainWindow::stopClicked()
{
   // disconnect(timer,SIGNAL(timeout()),simulation,SLOT(run()));
    if (status == true)
    {
        pscene->coreInterface->tellSysManagerStop();
        ui->actionStart->setDisabled(false);
        ui->actionPause->setDisabled(false);
        status = false;
    }
    else
    {
        qDebug()<<"System is not started yet";
    }
}

void MainWindow::stepForwardClicked()
{
    if(status == true)
    {
        qDebug()<<"Stepping forward";
        pscene->coreInterface->tellSysManagerStepFwd();
    }
    else
    {
        qDebug()<<"System is not started yet";
    }
}

void MainWindow::stepBackwardClicked()
{
    if(status == true)
    {
        qDebug()<<"Stepping backward";
    }
    else
    {
        qDebug()<<"System is not started yet";
    }
}

void MainWindow::pauseClicked()
{

    if (status == true)
    {
        qDebug()<<"Pausing";
        ui->actionPause->setDisabled(true);
        ui->actionStart->setDisabled(false);
    }
    else
    {
        qDebug()<<"System is not started yet";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
