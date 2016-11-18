#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H
#include <QDebug>

#include <QObject>
#include <QTimer>
#include <QTime>
#include <EntitySystem/Systems/system.h>
#include <EntitySystem/Systems/stpsystem.h>

class SystemManager : public QObject
{
    Q_OBJECT
public:
   SystemManager(EntityManager * man=0, QObject *parent=0);
    bool sysManagerStart();
    void sysManagerStop();
    void sysManagerStepFwd();

private:
    QTimer *timer;
    int fps;
    bool trigger;
    QList<System*> systems;
    StpSystem * stpSystem;
    EntityManager * manager;

    void test();

signals:

public slots:
    void update();
};

#endif // SIMULATION_H
