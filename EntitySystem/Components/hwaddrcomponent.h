#ifndef HWADDRCOMPONENT_H
#define HWADDRCOMPONENT_H
#include <EntitySystem/Components/component.h>


struct HwAddrComponent
{



private:

    uint A = qrand() % ((255+1) - 1) +1;
    uint B = qrand() % ((255+1) - 1) +1;
    uint C = qrand() % ((255+1) - 1) +1;
    uint D = qrand() % ((255+1) - 1) +1;
    uint E = qrand() % ((255+1) - 1) +1;
    uint F = qrand() % ((255+1) - 1) +1;
public:
    QString mac = QString("%1").arg(A,1,16)+":"+QString("%1").arg(B,1,16)+":"+QString("%1").arg(C,1,16)+":"+QString("%1").arg(D,1,16)
            +":"+QString("%1").arg(E,1,16)+":"+QString("%1").arg(F,1,16);
};

#endif // HWADDRCOMPONENT_H
