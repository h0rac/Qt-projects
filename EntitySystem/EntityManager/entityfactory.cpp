#include "entityfactory.h"

EntityFactory::EntityFactory()
{
manager = new EntityManager();
//manager->init();
}


uint EntityFactory::produceSwitch(QString portType,uint portNum)
{

    #define SWITCHCOMPONENTS (ComponentInterface|ComponentHostname|ComponentStp|ComponentMac)

    //uint _switch = manager->createEntityWithComponents(SWITCHCOMPONENTS);
    uint _switch = manager->createEntity();
    manager->addComponent(_switch,ComponentInterface);
    manager->addComponent(_switch,ComponentHostname);
    manager->addComponent(_switch,ComponentMac);
    manager->addComponent(_switch,ComponentStp);



    for(uint p = 0; p < portNum; p++)
    {


       NetInterfaceComponent *intf =  new NetInterfaceComponent(portType,p);
       qDebug()<<"APPEND intf"<<intf;

       manager->NetInterfaceComponents.append(qMakePair(_switch,intf));

     }
    qDebug()<<manager->NetInterfaceComponents;

    manager->HostnameComponents[_switch] = HostnameComponent{"Switch"};
    manager->HwAddrComponents[_switch] = HwAddrComponent{};
    manager->StpComponents[_switch] = StpComponent{};


return _switch;
}
uint EntityFactory::produceRouter(QString portType, uint portNum)
{
    #define ROUTERCOMPONENTS (ComponentInterface|ComponentHostname|ComponentMac)

    //uint router = manager->createEntityWithComponents(ROUTERCOMPONENTS);

    uint router = manager->createEntity();
    manager->addComponent(router,ComponentInterface);
    manager->addComponent(router,ComponentHostname);
    manager->addComponent(router,ComponentMac);

    for(uint p = 0; p < portNum; p++)
    {


       NetInterfaceComponent *intf =  new NetInterfaceComponent(portType,p);
       qDebug()<<"APPEND intf"<<intf;

       manager->NetInterfaceComponents.append(qMakePair(router,intf));


     }
   qDebug()<<manager->NetInterfaceComponents;
   manager->HostnameComponents[router] = HostnameComponent{"Router"};
   manager->HwAddrComponents[router] = HwAddrComponent{};

   return router;
}
EntityFactory::~EntityFactory()
{
    delete manager;
}

