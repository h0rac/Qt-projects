#ifndef STPCOMPONENT_H
#define STPCOMPONENT_H
#include <QString>
#include <EntitySystem/Components/component.h>


struct StpComponent
{

    bool blocking = true;
    bool listening = false;
    bool learning = false;
    bool forwarding = false;

};

#endif // STCOMPONENT_H
