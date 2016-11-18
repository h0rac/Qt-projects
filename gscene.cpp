#include <gscene.h>
#include <iostream>
#include <QtDebug>
#include <QString>
#include <QPen>
#include <gui/gdevconnector.h>
#include <ui_mainwindow.h>
#include <windows/mainwindow.h>
#include <QTimer>
#include <QGraphicsTextItem>


GScene::GScene(QObject *parent):QGraphicsScene(parent)
{
 qDebug("Dziala konstruktor GScene");
 rcount = 0;
 swcount=0;
 presscount=0;
 id = 0;
 model = new QStandardItemModel();
 coreInterface = new CoreInterface();
 widget = new GDevWidget();
 //model->setVerticalHeaderItem(0,new QStandardItem(QString("Active Devices")));



}

void GScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseDoubleClickEvent(event);

    QPointF pt = event->scenePos();
    qDebug()<<"Position"<<pt;
    qDebug()<<"Test choice selected"<<choice;
    bool flag = true;

    plist= window->getActDevListView();

    while (flag)
    {

        if (choice == "Switch" && event->button() == Qt::LeftButton && swcount < UINT_MAX)
        {
            swcount++;
            id++;
            intitialHost = "SW"+QString::number(swcount);
            qDebug()<<"Wybrano"<<choice;
            gNetdev = new GNetDevice(intitialHost,choice,id);
            widget->pdev = gNetdev;

            QString devName = widget->pdev->getName();
            widget->setText(devName);
            qDebug()<<"widget name"<<devName;
            //model->appendRow(widget);
            //plist->setModel(model);


            this->addItem(gNetdev);
            //text->setPos(pt.x(),pt.y()-60);
            gNetdev->setPos(pt);
            qDebug()<<"in position"<<gNetdev->scenePos();
            qDebug()<<"on scene items"<<this->items();
            gNetdev->update();
            qDebug()<<"switch id"<<id;


            coreInterface->tellCreateDevice(1);

            widget->pdev->getCoreInterface(coreInterface);

            widget->pdev->setGScenePtr(this);

            flag = false;
        }
        else if (choice == "Router" && event->button() == Qt::LeftButton && rcount < UINT_MAX)
        {
            rcount++;
            id++;

            intitialHost = "R"+QString::number(rcount);
            gNetdev = new GNetDevice(intitialHost ,choice,id);
            widget->pdev = gNetdev;
            QString devName = gNetdev->getName();
            widget->setText(devName);
            qDebug()<<"widget name"<<devName;
            qDebug()<<"getActDevList is"<<plist;
            //model->appendRow(widget);
            //plist->setModel(model);
            this->addItem(gNetdev);
            gNetdev->setPos(pt);

            gNetdev->update();
            qDebug()<<"Wybrano"<<choice;
            qDebug()<<"router ID"<<id;

            coreInterface->tellCreateDevice(2);
            coreInterface->tellTestEntityDatabase();


            widget->pdev->getCoreInterface(coreInterface);

            widget->pdev->setGScenePtr(this);

            flag = false;

        }
        else
        {
            break;
        }

    }
}

void GScene::tellGnetDevSetConnection(QString srcInterface, QString dstInterface,uint srcID,uint dstID)
{
    srcIntf=srcInterface;
    dstIntf = dstInterface;
    srcEntity = srcID;
    dstEntity = dstID;

    qDebug()<<"TEST1"<<srcIntf;
    qDebug()<<"TEST2"<<dstIntf;
    qDebug()<<"TEST3"<<srcEntity;
    qDebug()<<"TEST4"<<dstEntity;
}

void GScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);

    fromSrc = event->scenePos();

    if (event->button() == Qt::LeftButton && choice=="Connect")
    {

        presscount++;
        qDebug()<<"GScene Presscount count"<<presscount;
        if(presscount == 1)
        {

            pgitem = this->itemAt(fromSrc,QTransform());
            if (pgitem != 0)
            {
                item1 = dynamic_cast<GNetDevice*>(pgitem);
                if (item1 != 0)
                {
                    srcItemID = item1->getID();
                    qDebug()<<"ITEM1 TYPEID"<<typeid(item1).name();
                    //CREATE MENU FOR GNETDEV BASE ON ID
                    gNetdev->createMenu(item1->getID());

                }
            }
        }

       else if(presscount > 2)
       {
            presscount = 0;
            toDst = event->scenePos();
            pgitem = this->itemAt(toDst,QTransform());
            if (pgitem != 0 && pgitem != item1)
            {
                item2 = dynamic_cast<GNetDevice*>(pgitem);
                if (item2 != 0)
                {
                    dstItemID = item2->getID();
                    qDebug()<<"ITEM2 TYPEID"<<typeid(item2).name();
                    //CREATE MENU FOR GNETDEV BASE ON ID

                    gNetdev->createMenu(item2->getID());


                    if((srcEntity == srcItemID && dstEntity == dstItemID) /*|| (srcEntity == dstItemID && dstEntity == srcItemID)*/)
                    {
                        if(item1 != 0 && item2 != 0)
                        {
                            if(coreInterface->tellSetDataForConnection(srcIntf,dstIntf,srcEntity,dstEntity)== true)
                            {
                                qDebug()<<"TRUE RETURNED";

                                conn = new GDevConnector();
                                conn->setZValue(-1.0);
                                conn->connect(item1,item2,srcIntf,dstIntf);
                                item1->addConnector(conn);
                                item2->addConnector(conn);
                                conn->drawConnection();
                                this->addItem(conn);

                                coreInterface->tellTestEntityDatabase();

                            }
                            else
                            {
                                qDebug("Error connection cannot be established");
                            }
                        }
                        else
                        {
                            qDebug()<<"Error to set item1"<<item1;
                            qDebug()<<"Error,to set item2"<<item2;
                        }
                    }

                   else
                   {
                        qDebug("Error, abort drawning");
                   }
                }
            }
        }

     }

    if (event->button() == Qt::LeftButton && choice=="Select")
    {
       QPointF selection = event->scenePos();
       pgitem = this->itemAt(selection,QTransform());
       if (pgitem != 0 && pgitem != item1 && pgitem != item2)
       {
         conn = dynamic_cast<GDevConnector*>(pgitem);
           if (conn != 0)
           {
               qDebug()<<"selected connector"<<conn;
               QMessageBox *warning = new QMessageBox();
               warning->setText("Do you want to remove following connection ? <br>"+
                                conn->fromSrc->hostText->toPlainText()+" interface "+conn->srcInterface+" -----> "+conn->toDst->hostText->toPlainText()+" interface "+conn->dstInterface);

               warning->setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
               warning->setDefaultButton(QMessageBox::Cancel);
               int ret = warning->exec();
               switch(ret)
               {
                   case QMessageBox::Ok:
                        qDebug("Item will be removed");

                        coreInterface->tellDelDataForConnection(conn->srcInterface,conn->dstInterface,conn->fromSrc->getID(),conn->toDst->getID());
                        conn->fromSrc->delConnector(conn);
                        conn->toDst->delConnector(conn);
                        this->removeItem(conn);
                        break;
                   case QMessageBox::Cancel:
                        qDebug("Canceled");
                   break;
               }
               delete warning;
           }
       }
    }
}

void GScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
}

void GScene::keyPressEvent(QKeyEvent *event)
{
    QList<QGraphicsItem*>sceneItems = this->items();

    if (event->key() == Qt::Key_Delete)
    {
        std::unique_ptr<QMessageBox>warnnings;

        QMessageBox *warning = new QMessageBox();
        warning->setText("Do you want to remove all items ?");

        warning->setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
        warning->setDefaultButton(QMessageBox::Cancel);
        int ret = warning->exec();
        foreach(QGraphicsItem *item, sceneItems)
        {
            switch(ret)
            {
                case QMessageBox::Ok:
                    qDebug("Delete key pressed");
                    swcount = 0;
                    rcount = 0;
                    coreInterface->tellClearConnections();
                    coreInterface->tellRemoveEntities();
                    this->removeItem(item);
                    break;
                case QMessageBox::Cancel:
                    qDebug("Canceled");
                    break;
                }
        }
        delete warning;

    }

}
void GScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);

}


void GScene::setChoice(QString &ch)
{
    choice = ch;
    qDebug()<<"Choice set to"<<ch;

}
QString GScene::getChoice() const
{
    return choice;
}

void  GScene::getMainWindow(MainWindow *ptr)
{
    window = ptr;
}
QStandardItemModel * GScene::getActDevModel()
{
    return model;
}


GScene::~GScene()
{
 qDebug("Dziala destruktor GScene");

 delete model;
 delete coreInterface;
 delete widget;

}

