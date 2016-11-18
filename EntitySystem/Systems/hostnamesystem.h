#ifndef HOSTNAMESYSTEM_H
#define HOSTNAMESYSTEM_H
#include <EntitySystem/Systems/system.h>


class HostnameSystem : public System
{
    Q_OBJECT
public:
    HostnameSystem(EntityManager *man=0);
    EntityManager *manager;
    void update();
    void setHostname(QString name, uint entityID);
};

#endif // HOSTNAMESYSTEM_H
