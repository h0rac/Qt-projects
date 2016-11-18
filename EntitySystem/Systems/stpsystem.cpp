#include "stpsystem.h"

StpSystem::StpSystem(EntityManager * man):System(man),manager(man)
{

}

void StpSystem::createBPDU()
{
    //retrieve macs
}

QList<QPair<uint,int> > StpSystem::getConvertedToIntHwAddresses(QList<QPair<uint,HwAddrComponent*> > macAddrs)
{
    QPair<uint,HwAddrComponent*> pair1;

    QPair<uint,QStringList> mypair;
    QList<QPair<uint,int> >sumConvertedMac;
    QList<QPair<uint,QStringList> > strListMac;
    bool ok;

    foreach(pair1, macAddrs)
    {
        qDebug()<<"pair id"<<pair1.first;
        qDebug()<<"pair mac"<<pair1.second->mac;
        strListMac.append(qMakePair(pair1.first,pair1.second->mac.split(':')));

    }
     qDebug()<<"++MACS++"<<strListMac;

     foreach(mypair,strListMac)
     {
         int sum = 0;
           qDebug()<<"mypair.second"<<mypair.second;

         foreach(QString mac, mypair.second)
         {


             qDebug()<<"++int mac++"<<mac.toInt(&ok,16);
             sum += mac.toInt(&ok,16);

         }
           qDebug()<<"++sum++"<<sum;
           sumConvertedMac.append(qMakePair(mypair.first,sum));

     }
     return sumConvertedMac;

}


void StpSystem::update()
{
    qDebug()<<"Stp system run";

    QPair<uint,NetInterfaceComponent*> pair;


    QList<QPair<uint,HwAddrComponent*> >macAddresses;


    HwAddrComponent * pmac = nullptr;

    for(uint e= 0; e < MAX_ENTITIES; e++)
    {

            if(manager->componentMasks[e].contains(ComponentConnection) && manager->componentMasks[e].contains(ComponentStp))
            {
                if(manager->componentMasks[e].contains(ComponentMac))
                {
                     pmac = &manager->HwAddrComponents[e];
                     macAddresses.append(qMakePair(e,pmac));
                }


                foreach(ConnectionComponent conn ,manager->ConnectionComponents)
                {

                    foreach(pair, conn.dstInterfaces)
                    {
                         qDebug()<<"DSTINTERFACES LIST";

                        qDebug()<<"pair first"<<pair.first;
                        qDebug()<<"pair second"<<pair.second->m_type<<pair.second->port;
                    }

                    foreach(pair, conn.srcInterfaces)
                    {
                        qDebug()<<"SRCINTERFACES LIST";

                        qDebug()<<"pair first"<<pair.first;
                        qDebug()<<"pair second"<<pair.second->m_type<<pair.second->port;


                    }
                }

            }
        }

    qDebug()<<"TEST"<<macAddresses;

     QList<QPair<uint,int> > convertedMacs = getConvertedToIntHwAddresses(macAddresses);
     qDebug()<<"++convertedMac++"<<convertedMacs;




}








