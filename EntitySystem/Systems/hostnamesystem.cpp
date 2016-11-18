#include "hostnamesystem.h"

HostnameSystem::HostnameSystem(EntityManager * man):System(man),manager(man)
{

}
void HostnameSystem::update()
{


}
void HostnameSystem::setHostname(QString name,uint entityID)
{
     qDebug()<<"Core recv hostname"<<name;
     qDebug()<<"Core recv entityID"<<entityID;

     HostnameComponent * host;
     if(manager->componentMasks[entityID].contains(ComponentHostname))
     {
        host = &manager->HostnameComponents[entityID];
        host->hostname = name;

     }
 }
