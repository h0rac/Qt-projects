#ifndef COREINTERFACE_H
#define COREINTERFACE_H
#include <EntitySystem/EntityManager/entityfactory.h>
#include <EntitySystem/Systems/connectionsystem.h>
#include <EntitySystem/Systems/hostnamesystem.h>
#include <QDebug>
#include <gui/gdevconnector.h>
#include <core/sysmanager.h>

class CoreInterface
{

private:
    SystemManager * sysmanager;
    ConnectionSystem * connSystem;
    HostnameSystem * hostnameSystem;
    EntityFactory *factory;
    bool status;

public:
    CoreInterface();
    ~CoreInterface();

    bool tellSysManagerStart();
    void tellSysManagerStop();
    void tellSysManagerPause();
    void tellSysManagerStepFwd();
    void tellSysManagerStepBck();
    void tellCreateDevice(uint type);
    void tellClearConnections();
    void tellRemoveEntities();
    void tellSetHostname(QString name, uint entityID);
    QList<QString> tellGetDstConnectionInfo(uint entityID);
    bool tellSetDataForConnection(QString srcInterface, QString dstInterface,uint srcID, uint dstID);
    bool tellDelDataForConnection(QString srcInterface, QString dstInterface,uint srcID, uint dstID);
    void tellTestEntityDatabase();
    QList<QPair<QString, bool> > tellGetInterfaceList(uint entityID);


};

#endif // COREINTERFACE_H
