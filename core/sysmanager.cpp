#include "sysmanager.h"

SystemManager::SystemManager(EntityManager *man, QObject *parent) : manager(man),QObject(parent)
{
    //call update every 2 seconds
    timer = new QTimer();
   // connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    connect(timer,&QTimer::timeout,this,&SystemManager::update);

    stpSystem = new StpSystem(manager);
    systems.append(stpSystem);
    trigger = false;

}


bool SystemManager::sysManagerStart()
{
    timer->start(2000);
    timer->setSingleShot(false);
    qDebug()<<"system started";
    return true;
}
void SystemManager::sysManagerStop()
{
    timer->stop();
    qDebug()<<"system stopped";

}
void SystemManager::sysManagerStepFwd()
{
    timer->setSingleShot(true);
    qDebug()<<"system step forward";

}

void SystemManager::test()
{
    qDebug()<<"fake test of system run";
}

void SystemManager::update()
{
    qDebug()<<"update called";
    foreach(System * sys, systems)
    {
        sys->update();
    }
}



