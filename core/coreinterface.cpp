#include "coreinterface.h"

CoreInterface::CoreInterface()
{
    factory = new EntityFactory();
    connSystem = new ConnectionSystem(factory->manager);
    hostnameSystem = new HostnameSystem(factory->manager);
    sysmanager = new SystemManager(factory->manager);
}

void CoreInterface::tellTestEntityDatabase()
{


}
void CoreInterface::tellRemoveEntities()
{
    factory->manager->destroyAllEntities();
}

void CoreInterface::tellSetHostname(QString name, uint entityID)
{

   if (hostnameSystem != nullptr)
   {
    hostnameSystem->setHostname(name,entityID);
   }
   else
   {
        qDebug()<<"Error to cast system to hostnameSystem";
   }
}

void  CoreInterface::tellCreateDevice(uint type)
{
    uint entity;
    switch(type)
    {
    case 1:
         entity = factory->produceSwitch("GigabitEthernet",5);
        break;
    case 2:
        entity= factory->produceRouter("GigabitEthernet",3);
        break;
    }
}
/*
QList<QString> CoreInterface::tellGetDstConnectionInfo(uint entityID)
{
    if (connSystem != nullptr)
    {
      return connSystem->getDstConnectionInfo(entityID);
    }
    else
    {
        qDebug()<<"Error ptr (getConnectionData)";
    }
}
*/
QList<QPair<QString,bool> >CoreInterface::tellGetInterfaceList(uint entityID)
{
    if (connSystem != nullptr)
    {
      return connSystem->getInterfaceList(entityID);
    }
    else
    {
        qDebug()<<"Error ptr (getInterfaceData)";
    }



}
bool CoreInterface::tellSetDataForConnection(QString srcInterface, QString dstInterface, uint srcID, uint dstID)
{
    //qDebug()<<"[+]-----in CoreInterface--------[+]";
    //qDebug()<<"srcInterface"<<srcInterface<<"srcID "<<srcID;
    //qDebug()<<"dstInterface"<<dstInterface<<"dstID "<<dstID;
    if (connSystem != nullptr)
    {
        if(connSystem->processConnection(srcInterface,dstInterface,srcID,dstID) == true)
        {
            return true;
        }
        else
        {
            qDebug("Error,coreInterface is not able to setData for Connection");
            return false;
        }
    }
    else
    {
        qDebug()<<"Error ptr  (setDataForConnection)";
        return false;
    }

}
bool CoreInterface::tellDelDataForConnection(QString srcInterface, QString dstInterface, uint srcID, uint dstID)
{
    if (connSystem != nullptr)
    {
        if (connSystem->processConnection(srcInterface,dstInterface,srcID,dstID,1))
        {
            return true;
        }
        else
        {
            qDebug("Error,connection deleted unsuccessfuly");
            return false;
        }
    }
    else
    {
        qDebug()<<"Error ptr  (delDataForConnection)";
        return false;
    }

}
void CoreInterface::tellClearConnections()
{
    if(connSystem != nullptr)
    {
        connSystem->clearConnections();
    }
    else
    {
        qDebug()<<"Error ptr  to system (delConnections)";
    }

}
bool CoreInterface::tellSysManagerStart()
{
    for(uint e = 0; e < MAX_ENTITIES; e++)
    {
        if(factory->manager->componentMasks[e].contains(ComponentConnection))
        {
            foreach(ConnectionComponent conn, factory->manager->ConnectionComponents)
            {
                if(!(conn.srcInterfaces.isEmpty() && conn.dstInterfaces.isEmpty()))
                {
                    sysmanager->sysManagerStart();
                    return true;
                }
            }
        }
        else
        {
            qDebug()<<"No connections available for simulation";
            continue;

        }
    }
    return false;


}

void CoreInterface::tellSysManagerStop()
{
    sysmanager->sysManagerStop();
}

void CoreInterface::tellSysManagerPause()
{

}

void CoreInterface::tellSysManagerStepFwd()
{
    sysmanager->sysManagerStepFwd();
}

void CoreInterface::tellSysManagerStepBck()
{

}


CoreInterface::~CoreInterface()
{

    delete factory;
    delete hostnameSystem;
    delete connSystem;
}



