#include "entitymanager.h"
#include <QDebug>




EntityManager::EntityManager()
{
 id=0;
 HostnameComponents.resize(MAX_ENTITIES);
 HwAddrComponents.resize(MAX_ENTITIES);
 StpComponents.resize(MAX_ENTITIES);
 ConnectionComponents.resize(MAX_ENTITIES);
 componentMasks.resize(MAX_ENTITIES);
}
uint EntityManager::createEntity()
{
    if (id < MAX_ENTITIES)
    {
       id++;
    }
    return id;

}

void EntityManager::addComponent(uint e, uint c)
{
    if (!componentMasks[e].contains(c))
    {
          componentMasks[e].append(c);
    }
    qDebug()<<"ComponentMasks"<<componentMasks[e];
}

void EntityManager::removeComponent(uint e, uint c)
{

    if(componentMasks[e].contains(c))
    {
      componentMasks[e].removeAll(c);
    }
}
void EntityManager::destroyAllEntities()
{

    for(uint i =0; i < MAX_ENTITIES; i++)
    {
        //qDebug()<<"componentMasks"<<componentMasks[i];
        componentMasks[i].clear();

    }
    NetInterfaceComponents.clear();

}
void EntityManager::destroyEntity(uint entity)
{
    components[entity] = ComponentNone;
}


























