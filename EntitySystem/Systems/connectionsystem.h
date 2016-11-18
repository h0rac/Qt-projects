#ifndef CONNECTIONSYSTEM_H
#define CONNECTIONSYSTEM_H
#include <EntitySystem/Systems/system.h>
#include <EntitySystem/Components/netinterfacecomponent.h>
#include <EntitySystem/EntityManager/entitymanager.h>
#include <EntitySystem/Components/connectioncomponent.h>
#include <QDebug>
#include <QMenu>
#include <QListWidget>



class ConnectionSystem : public System
{
    Q_OBJECT

public:
    EntityManager *manager;
    ConnectionSystem(EntityManager *man=0);
    void update();
    QList<NetInterfaceComponent> NetInterfaces;
    QList<NetInterfaceComponent> vectorData;



    QList<QString> getDstConnectionInfo(uint entityID);


    QHash<QString,QHash<uint,NetInterfaceComponent*> > guiMapper;

    QList<QPair<QString, bool> > getInterfaceList(uint entityID);

    void setMapping(QString guInterface, uint entityID,NetInterfaceComponent *interface);

    bool processConnection(QString srcIntf, QString dstIntf, uint srcEntity, uint dstEntity, uint action=0);

    bool setConnection(NetInterfaceComponent *srcIntf, NetInterfaceComponent *dstIntf, uint srcEntity, uint dstEntity);

    bool delConnection(NetInterfaceComponent *srcIntf, NetInterfaceComponent *dstIntf, uint srcEntity, uint dstEntity);

    void clearConnections();


};

#endif // CONNECTIONSYSTEM_H
