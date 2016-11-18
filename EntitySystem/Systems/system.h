#ifndef SYSTEM_H
#define SYSTEM_H
#include <EntitySystem/EntityManager/entitymanager.h>
#include <EntitySystem/EntityManager/entityfactory.h>
#include <gui/guiinterface.h>
#include <QStateMachine>
#include <QState>
#include <QFinalState>

class System:public QObject
{
    Q_OBJECT
public:
    System(EntityManager *man=0);
    EntityManager *manager;
    virtual void update(){}
};

#endif // SYSTEM_H
