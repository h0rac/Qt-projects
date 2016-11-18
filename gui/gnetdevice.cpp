#include <gui/gnetdevice.h>
#include <QDebug>
#include <qvector2d.h>


GNetDevice::GNetDevice(QString name, QString itype,uint id):QGraphicsPixmapItem(),m_name(name),m_itype(itype),m_id(id)
{
    m_htypes["Switch"] = ":/switch.jpg";
    m_htypes["Router"] = ":/router.jpg";
    qDebug("Dziala konstruktor NetDevice");
    QString selected = m_htypes.value(m_itype);
    qDebug()<<"Selected image"<<selected;
    QPixmap pixmap(selected);
    this->boundingRect();
    this->setPixmap(pixmap);
    this->setVisible(true);
    this->setFlag(ItemSendsGeometryChanges);
    this->setFlag(ItemIsMovable);
    this->setFlag(ItemIsSelectable);
    //qDebug()<<"test pixmap"<<this->pixmap();
    mapper = new Mapper();
    mapper->setGnetDevPtr(this);

    hostText = new QGraphicsTextItem;

    presscount = 0;


}

QVariant GNetDevice::itemChange(GraphicsItemChange change, const QVariant & value)
{
    //qDebug()<<"Change"<<change;
    if (change == this->ItemPositionChange)
    {
        foreach(GDevConnector *conn, connectors)
        {
           conn->drawConnection();
           conn->update();
        }
    hostText->setPos(this->x()+30,this->y()-20);
    hostText->update();
    }
    return value;
}
void GNetDevice::setHostname(QString text)
{
    hostText->setPlainText(text);
    coreInterface->tellSetHostname(text,m_id);
}

QString GNetDevice::getName()
{
    return m_name;
}
uint GNetDevice::getID()
{
    if(m_id > 0 )
    {
        return m_id;
    }
}

void GNetDevice::addConnector(GDevConnector *conn)
{
    if (!connectors.contains(conn))
    {
        connectors.append(conn);
    }
    qDebug()<<"connectors"<<connectors;
}

void GNetDevice::delConnector(GDevConnector *conn)
{
    if(connectors.contains(conn))
    {
        connectors.removeOne(conn);
    }
    else
    {
        qDebug()<<"Problem to remove"<<conn;
    }
    qDebug()<<"connectors"<<connectors;
}



void GNetDevice::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{


   //QList<QString>connections = coreInterface->getConnectionData(getID());
    QMenu * menu = new QMenu();
    QSignalMapper *signalmap1;
    QAction * action = new QAction("Change hostname",menu);

    signalmap1 = new QSignalMapper(action);
    signalmap1->setMapping(action,m_id);

    menu->addAction(action);
    mapper->connect(action, SIGNAL(triggered()), signalmap1, SLOT(map()));
    mapper->connect(signalmap1, SIGNAL(mapped(int)), mapper, SLOT(menuItemClicked(int)));

    menu->popup(QCursor::pos());

   // delete signalmap1;

}


void GNetDevice::getCoreInterface(CoreInterface *interface)
{
    coreInterface = interface;
}

void GNetDevice::createMenu(uint devID)
{

    QList<QPair<QString,bool> >interfaces = coreInterface->tellGetInterfaceList(devID);
        QMenu * menu = new QMenu();

        qDebug()<<"FOR MENU INTF LIST"<<interfaces;

        QSignalMapper *signalmap;
        //menu->setWindowModality(Qt::WindowModal);

        qDebug()<<"id in gnet"<<devID;
        QPair<QString,bool> pair;

        QIcon icon;
        icon.addFile("/home/horac/simpro/icons/ethOn.png",QSize(32,32),QIcon::Disabled,QIcon::On);
        icon.addFile("/home/horac/simpro/icons/ethOff.png",QSize(32,32),QIcon::Normal,QIcon::Off);

        foreach(pair, interfaces)
        {

            QAction * action = new QAction(icon,pair.first,menu);

            qDebug()<<"INTERFACE STATE IN MENU"<<pair.second;

            if (pair.second == true)
            {
                action->setIcon(QIcon(QPixmap(":/ethOn.png")));
            }
            else
            {
                action->setIcon(QIcon(QPixmap(":/ethOff.png")));
            }


           signalmap = new QSignalMapper(action);
           signalmap->setMapping(action,devID);

            menu->addAction(action);
            mapper->connect(action, SIGNAL(triggered()), signalmap, SLOT(map()));
            mapper->connect(signalmap, SIGNAL(mapped(int)), mapper, SLOT(deviceClicked(int)));

            menu->addSeparator();

            //mapper->connect(action,&QAction::triggered,mapper,&Mapper::deviceClicked);

            qDebug()<<"Interface -"<<pair.first<<"state-"<<pair.second;


        }
        menu->exec(QCursor::pos());

        delete signalmap;
        delete menu;


}

void GNetDevice::setDataAfterClick(QString interface,uint id)
{
    qDebug()<<"Selected interface"<<interface<<"ID"<<id;

    presscount++;

    if(presscount == 1)
    {
        temp1 = interface;

        tempSrcID = id;
    }
    else if (presscount >= 2)
    {



        temp2 = interface;
        tempDstID = id;

        scene->tellGnetDevSetConnection(temp1,temp2,tempSrcID,tempDstID);

         presscount =0;

       qDebug("########GNETDEVICE##########");
       qDebug()<<"temp1"<<temp1<<"srcID"<<tempSrcID;
       qDebug()<<"temp2"<<temp2<<"dstID"<<tempDstID;

    }
}

void GNetDevice::setHostnameWidget()
{

   chostwidget = new HostnameWidget();
   chostwidget->setGNetDevPtr(this);
}



void GNetDevice::setGScenePtr(GScene *gscene)
{
    scene = gscene;
    initializeHostname();


}
void GNetDevice::initializeHostname()
{
    if (hostText != nullptr)
    {
        hostText->setPlainText(m_name);
        hostText->setDefaultTextColor(Qt::black);
        hostText->setFont(QFont("times",12));
        hostText->setFlag(ItemSendsGeometryChanges);
        qDebug()<<this->boundingRect();
        hostText->setPos(this->x()+30,this->y()-20);
        scene->addItem(hostText);


    }
    else
    {
        qDebug()<<"Error to set hostText ptr";
    }
}

void GNetDevice::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    //QPointF V = event->scenePos();
    //hostText->setPos(V);
}


bool GNetDevice::removeConnection()
{
    coreInterface->tellDelDataForConnection(temp1,temp2,tempSrcID,tempDstID);
    return true;
}

GNetDevice::~GNetDevice()
{
    connectors.clear();
    delete mapper;
    delete hostText;

}

void GNetDevice::mouseMoveEvent( QGraphicsSceneMouseEvent *event )
{
    QGraphicsItem::mouseMoveEvent(event);
    //QPointF V = event->scenePos();
   // hostText->setPos(V);




    /*

    if (this->x() < 0)
    {
        setPos(0, y());
    }
    else if (this->x() + boundingRect().right() > scene->width())
    {
        setPos(scene->width() - boundingRect().width(), this->y());
    }

    if (this->y() < 0)
    {
        setPos(x(), 0);
    }
    else if ( this->y()+ boundingRect().bottom() > scene->height())
    {
        setPos(this->x(), scene->height() - boundingRect().height());
    }
    */
}


