#include "windows/mainwindow.h"
#include <QApplication>
#include <EntitySystem/EntityManager/entitymanager.h>
#include <QDebug>
#include <EntitySystem/Components/netinterfacecomponent.h>
#include <EntitySystem/Components/stpcomponent.h>
#include <EntitySystem/EntityManager/entityfactory.h>
#include <EntitySystem/Systems/system.h>
#include <EntitySystem/Systems/connectionsystem.h>
#include <core/coreinterface.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.processEvents();
    MainWindow w;



    w.show();

    return a.exec();
}
