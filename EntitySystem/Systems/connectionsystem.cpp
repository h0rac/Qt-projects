#include "connectionsystem.h"
#include <QSignalMapper>
#include <typeinfo>


ConnectionSystem::ConnectionSystem(EntityManager *man):System(man),manager(man)
{


}

void ConnectionSystem::update()
{

}

QList<QPair<QString,bool> >ConnectionSystem::getInterfaceList(uint entityID)
{
    qDebug()<<"manager->components[entityID]"<<manager->componentMasks[entityID];

    QList<QPair<QString,bool> > interfaces;

    if(manager->componentMasks[entityID].contains(ComponentInterface))
    {
        QPair<uint,NetInterfaceComponent*> pair;

        foreach(pair, manager->NetInterfaceComponents)
        {
            if(pair.first == entityID)
            {
                qDebug()<<"first"<<pair.first;
                qDebug()<<"second"<<pair.second;

                QString strInterface = pair.second->m_type+""+QString::number(0)+"/"+QString::number(pair.second->port);
                interfaces.append(qMakePair(strInterface,pair.second->state));
                setMapping(strInterface,entityID, pair.second);
            }

        }
        qDebug()<<"Interfaces before send"<<interfaces;
        return interfaces;
     }

}
 void ConnectionSystem::setMapping(QString strIntf,uint entityID,NetInterfaceComponent *intf)
 {
     guiMapper[strIntf][entityID] = intf;

 }

bool ConnectionSystem::processConnection(QString srcIntf, QString dstIntf, uint srcEntity, uint dstEntity,uint action)
{
    qDebug()<<"PROCESS CONNECTION RECV SRC INTF"<<srcIntf;
     qDebug()<<"PROCESS CONNECTION RECV DST INTF"<<dstIntf;

    NetInterfaceComponent *psrcIntf;
    NetInterfaceComponent *pdstIntf;


     QHash<uint,NetInterfaceComponent*> test1 = guiMapper.value(srcIntf);
     QHash<uint,NetInterfaceComponent*> test2 = guiMapper.value(dstIntf);
     psrcIntf = test1[srcEntity];
     pdstIntf = test2[dstEntity];
     qDebug()<<"test1"<<psrcIntf;
     qDebug()<<"test2"<<pdstIntf;


    if (action == 0)
    {
        if (setConnection(psrcIntf,pdstIntf,srcEntity,dstEntity) == true)
        {
            return true;
        }
        else
        {
            qDebug("Error, connection preparing failed");
            return false;
        }

    }
    else if(action == 1)
    {
      qDebug("###in delete action###");
      delConnection(psrcIntf,pdstIntf,srcEntity,dstEntity);
      return true;
    }
    else
    {
        //qDebug()<<"Error, wrong psrcInf"<<psrcIntf;
        //qDebug()<<"Error, wrong pdstIntf"<<pdstIntf;
        return false;
    }
}

bool ConnectionSystem::setConnection(NetInterfaceComponent *srcIntf, NetInterfaceComponent *dstIntf, uint srcEntity, uint dstEntity)
{


    ConnectionComponent srcConn;
    ConnectionComponent dstConn;

     manager->addComponent(srcEntity,ComponentConnection);
     manager->addComponent(dstEntity,ComponentConnection);

     if (srcEntity != dstEntity && dstEntity != srcEntity)
     {


         if (srcIntf->state == false && dstIntf->state== false)
         {


            if(!(srcConn.dstInterfaces.contains(qMakePair(dstEntity,dstIntf))
                    && dstConn.dstInterfaces.contains(qMakePair(srcEntity,srcIntf))
                    && srcConn.srcInterfaces.contains(qMakePair(srcEntity,srcIntf))
                    && dstConn.srcInterfaces.contains(qMakePair(dstEntity,dstIntf))))
            {

                srcConn.dstInterfaces.append(qMakePair(dstEntity,dstIntf));
                srcConn.srcInterfaces.append(qMakePair(srcEntity,srcIntf));
                dstConn.srcInterfaces.append(qMakePair(dstEntity,dstIntf));
                dstConn.dstInterfaces.append(qMakePair(srcEntity,srcIntf));

                manager->ConnectionComponents.push_back(srcConn);

                manager->ConnectionComponents.push_back(dstConn);

            }

            srcIntf->state = true;
            dstIntf->state = true;

            return true;
          }
          else
          {
            qDebug()<<srcIntf->m_type<<srcIntf->port<<"is already used"<<"on"<<srcEntity;
            qDebug()<<dstIntf->m_type<<dstIntf->port<<"is already used"<<"on"<<dstEntity;
            return false;
          }
      }
      else
      {
        qDebug()<<"Cannot loopback connections on the same device";
        return false;
     }
}

bool ConnectionSystem::delConnection(NetInterfaceComponent *srcIntf, NetInterfaceComponent *dstIntf, uint srcEntity, uint dstEntity)
{


    if (srcIntf->state == true && dstIntf->state== true)
    {
        qDebug()<<"checkpoint1";

            if (manager->componentMasks[srcEntity].contains( ComponentConnection))
            {

                QPair<uint,NetInterfaceComponent*> pair1;
                pair1.first = srcEntity;
                pair1.second = srcIntf;

                QPair<uint,NetInterfaceComponent*> pair2;
                pair2.first = dstEntity;
                pair2.second = dstIntf;

                for(uint e = 0; e < manager->ConnectionComponents.size(); e++)
                {
                    foreach(ConnectionComponent conn, manager->ConnectionComponents)
                    {
                        if(!(conn.srcInterfaces.isEmpty() && conn.dstInterfaces.isEmpty()))
                        {
                            manager->ConnectionComponents[e].srcInterfaces.removeAll(pair1);
                            manager->ConnectionComponents[e].dstInterfaces.removeAll(pair2);
                        }
                    }
                }


                qDebug()<<"del conn for"<<srcIntf->port<<"srcID"<<srcEntity;
                qDebug()<<"del conn for"<<dstIntf->port<<"dstID"<<dstEntity;

            }

           if(manager->componentMasks[dstEntity].contains(ComponentConnection))
           {

                QPair<uint,NetInterfaceComponent*> pair1;
                pair1.first = srcEntity;
                pair1.second = srcIntf;
                QPair<uint,NetInterfaceComponent*> pair2;
                pair2.first = dstEntity;
                pair2.second = dstIntf;

                for(uint e = 0; e < manager->ConnectionComponents.size(); e++)
                {
                    foreach(ConnectionComponent conn, manager->ConnectionComponents)
                    {
                        if(!(conn.srcInterfaces.isEmpty() && conn.dstInterfaces.isEmpty()))
                        {

                            manager->ConnectionComponents[e].srcInterfaces.removeAll(pair2);
                            manager->ConnectionComponents[e].dstInterfaces.removeAll(pair1);
                        }
                    }
                }

           }

        srcIntf->state = false;
        dstIntf->state = false;

        return true;
    }
    else
    {
     qDebug()<<srcIntf->m_type<<srcIntf->port<<"is already disconnected"<<"on"<<srcEntity;
     qDebug()<<dstIntf->m_type<<dstIntf->port<<"is already disconnected"<<"on"<<dstEntity;
     return false;
    }

}


void ConnectionSystem::clearConnections()
{

       guiMapper.clear();

       for(uint e = 0; e < manager->ConnectionComponents.size(); e++)
       {
           manager->ConnectionComponents[e].srcInterfaces.clear();
           manager->ConnectionComponents[e].dstInterfaces.clear();

       }
       qDebug("[-] CLEARING CONNECTIONS");
       qDebug()<<"guiMapper clear"<<guiMapper;

}


