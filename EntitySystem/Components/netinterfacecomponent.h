#ifndef NETINTERFACECOMPONENT_H
#define NETINTERFACECOMPONENT_H
#include <EntitySystem/Components/component.h>
#include <EntitySystem/EntityManager/entity.h>
#include <EntitySystem/Components/netinterfacecomponent.h>
#include <EntitySystem/Components/connectioncomponent.h>
#include <QIcon>
#include <QObject>
#include <EntitySystem/Components/portcomponent.h>
#include <bitset>
#include <QDebug>



struct NetInterfaceComponent
{
   //uint m_vlan;
   // QString m_vrf;


    QString m_type;
    uint port;

    PortComponent *p;

    bool state = false;


    NetInterfaceComponent(){}
    NetInterfaceComponent(QString type, uint port):
        m_type(type),port(port)
    {

    }
private:

    //QString A = QString::number(,16);
    uint A = qrand() % ((255+1) - 1) +1;
    uint B = qrand() % ((255+1) - 1) +1;
    uint C = qrand() % ((255+1) - 1) +1;
    uint D = qrand() % ((255+1) - 1) +1;
    uint E = qrand() % ((255+1) - 1) +1;
    uint F = qrand() % ((255+1) - 1) +1;

   QString mac = QString("%1").arg(A,1,16)+":"+QString("%1").arg(B,1,16)+":"+QString("%1").arg(C,1,16)+":"+QString("%1").arg(D,1,16)
            +":"+QString("%1").arg(E,1,16)+":"+QString("%1").arg(F,1,16);

};

#endif // NETINTERFACECOMPONENT_H
