#ifndef CONNECTIONCOMPONENT_H
#define CONNECTIONCOMPONENT_H
#include <EntitySystem/Components/netinterfacecomponent.h>

#include <QObject>

class NetInterfaceComponent;

struct ConnectionComponent
{

    QList<QPair<uint,NetInterfaceComponent*> >srcInterfaces;
    QList<QPair<uint,NetInterfaceComponent*> >dstInterfaces;


};

#endif // CONNECTIONCOMPONENT_H
