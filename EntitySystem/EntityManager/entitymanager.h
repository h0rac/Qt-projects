#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <EntitySystem/EntityManager/entity.h>
#include <QHash>
#include <QList>
#include <limits.h>
#include <QPair>
#include <iostream>
#include <EntitySystem/Components/netinterfacecomponent.h>
#include <EntitySystem/Components/hostnamecomponent.h>
#include <EntitySystem/Components/hwaddrcomponent.h>
#include <EntitySystem/Components/stpcomponent.h>
#include <EntitySystem/Components/connectioncomponent.h>
#include <EntitySystem/Components/netinterfacecomponent.h>
#include <EntitySystem/Components/portcomponent.h>

using namespace std;

const size_t MAX_ENTITIES = 10;

enum ComponentMasks
{
    ComponentNone = 0,
    ComponentInterface = 1,
    ComponentConnection = 2,
    ComponentHostname = 3,
    ComponentMac = 4,
    ComponentStp = 5,
    ComponentPort = 6

};


class EntityManager
{
private:
    uint id;
    uint e;

public:

    array<uint,MAX_ENTITIES>components;
    QVector<HostnameComponent> HostnameComponents;
    QVector<HwAddrComponent> HwAddrComponents;
    QVector<StpComponent>StpComponents;
    QVector<ConnectionComponent>ConnectionComponents;
    //QVector<NetInterfaceComponent>NetInterfaceComponents;
    QList<QPair<uint,NetInterfaceComponent* > >NetInterfaceComponents;
    QVector<PortComponent>PortComponents;

    vector<QList<uint> >componentMasks;
    uint createEntity();

    void addComponent(uint e, uint c);
    void removeComponent(uint e, uint c);


    EntityManager();

    void destroyAllEntities();
    void destroyEntity(uint entity);


};
#endif // ENTITYMANAGER_H
