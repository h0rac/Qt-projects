#ifndef STPSYSTEM_H
#define STPSYSTEM_H
#include <EntitySystem/Systems/system.h>


class StpSystem : public System
{


    Q_OBJECT

public:
    StpSystem(EntityManager * man=0);
    EntityManager * manager;
    void update();

private:
     QList<HwAddrComponent*> getMacs();
     QStateMachine machine;

     void createBPDU();

     QList<QPair<uint,int> >getConvertedToIntHwAddresses(QList<QPair<uint,HwAddrComponent*> > macAddrs);



};

#endif // STPSYSTEM_H
