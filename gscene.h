#ifndef GSCENE_H
#define GSCENE_H

#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QString>
#include <windows/mainwindow.h>
#include <gui/gnetdevice.h>
#include <gui/gdevconnector.h>
#include <gui/gdevwidget.h>
#include <windows/stpwindow.h>
#include <QStandardItemModel>
#include <QListView>
#include <QContextMenuEvent>
#include <QDebug>
#include <QMessageBox>
#include <typeinfo>

class MainWindow;
class GNetDevice;
class CoreInterface;
class GDevWidget;
class GDevConnector;

class GScene: public QGraphicsScene
{
    Q_OBJECT

private:

    QPointF fromSrc;
    QPointF toDst;
    QGraphicsItem *pgitem;
    GNetDevice *item1;
    GNetDevice *item2;
    MainWindow *window;
    StpWindow *stpwin;
    QListView *plist;
    GDevWidget *widget;
    QStandardItemModel *model;
    GDevConnector *conn;
    GNetDevice *gNetdev;

    QString choice;
    QString intitialHost;
    QString srcIntf;
    QString dstIntf;
    QString tempIntf;
    uint srcEntity;
    uint dstEntity;
    uint srcItemID;
    uint dstItemID;
    uint rcount;
    uint swcount;
    uint id;
    int presscount;

public:

    CoreInterface * coreInterface;
    GScene(QObject *parent = 0);
     ~GScene();

    void setChoice(QString &ch);
    QString getChoice() const;
    void getMainWindow(MainWindow *ptr);
    QStandardItemModel *getActDevModel();
    void tellGnetDevSetConnection(QString srcIntf, QString dstInterface, uint srcID, uint dstID);

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // GRAPHICSSCENE_H
