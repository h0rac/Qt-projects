#ifndef GNETDEVICE_H
#define GNETDEVICE_H

#include <QGraphicsPixmapItem>
#include <QHash>
#include <QPixmap>
#include <QVariant>
#include <QGraphicsItem>
#include <QList>
#include <gui/gdevconnector.h>
#include <QGraphicsSceneMouseEvent>
#include <QContextMenuEvent>
#include <QAction>
#include <EntitySystem/EntityManager/entity.h>
#include <EntitySystem/Components/netinterfacecomponent.h>
#include <core/coreinterface.h>
#include <gui/mapper.h>
#include <gscene.h>
#include <QPointer>
#include <QPainter>
#include <memory>
#include <hostnamewidget.h>
#include <QGraphicsTextItem>

class GDevConnector;
class CoreInterface;
class GScene;
class Mapper;
class HostnameWidget;

class GNetDevice: public QGraphicsPixmapItem
{

public:

    GNetDevice(QString name, QString itype, uint id);
    ~GNetDevice();
    void setHostname(QString text);
    void addConnector(GDevConnector * conn);
    void delConnector(GDevConnector * conn);
    QString getName();
    QList<GDevConnector*> getConnectors();
    void  getCoreInterface(CoreInterface *interface);
    void * getDevConnector(GDevConnector * connector);

    QGraphicsTextItem * hostText;

    void createMenu(uint devID);
    void setDataAfterClick(QString interface, uint id);
    void setHostnameWidget();

    uint getID();

    void setGScenePtr(GScene *gscene);
    bool removeConnection();

    //GScene * scene;

    GScene * scene;

    //std::unique_ptr<GScene> scene;


private:
    QString m_name;
    QString m_itype;
    QHash<QString,QString>m_htypes;
    QList<GDevConnector*>connectors;
    QVariant itemChange(GraphicsItemChange change, const QVariant & value);
    CoreInterface *coreInterface;
    int presscount;
    QGraphicsItem *pgitem;
    GNetDevice *item1;
    GNetDevice *item2;
    QPointF fromSrc;
    QPointF toDst;
    GDevConnector *conn;

    QString temp1;
    QString temp2;
    uint tempSrcID;
    uint tempDstID;
    Mapper * mapper;
    HostnameWidget * chostwidget;


    bool connectionSuccessfull;

    QString hostname;
    uint devID;
    uint m_id;
    void initializeHostname();
    QList<QString> interfaces;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void mouseMoveEvent( QGraphicsSceneMouseEvent *event );
};


#endif // GNETDEVICE_H
