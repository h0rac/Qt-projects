#include "windows/stpwindow.h"
#include "ui_stpwindow.h"
#include <QStandardItem>
#include <QDebug>

StpWindow::StpWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StpWindow)
{
    ui->setupUi(this);
    connect(ui->stpActDevView,&QListView::clicked,this,&StpWindow::getSTPViewItem);

}
QListView * StpWindow::setSTPactDevView()
{
    return ui->stpActDevView;
}

StpWindow::~StpWindow()
{
    delete ui;
}
void StpWindow::getSTPViewItem()
{
    qDebug("Item selected");
    //QString selected = stpmodel->data(&index, Qt::DisplayRole).toString();
    //qDebug()<<"Selected"<<selected;
}
void StpWindow::setStpModel(QStandardItemModel *model)
{
    stpmodel = model;

}
