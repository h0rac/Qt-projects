#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H
#include <EntitySystem/EntityManager/entity.h>
#include <EntitySystem/EntityManager/entitymanager.h>
#include <EntitySystem/Components/netinterfacecomponent.h>
#include <EntitySystem/Components/stpcomponent.h>
#include <EntitySystem/Components/hostnamecomponent.h>
#include <EntitySystem/Components/hwaddrcomponent.h>
#include <QDebug>

class EntityFactory
{
public:
    EntityFactory();
    ~EntityFactory();
    EntityManager * manager;
    uint produceSwitch(QString portType, uint portNum);
    uint produceRouter(QString portType, uint portNum);


    void testFactory();
};

#endif // ENTITYFACTORY_H
