#ifndef COMPONENT_H
#define COMPONENT_H
#include <QString>
#include <QObject>


class Component
{

public:
    QString componentName;
    Component(QString name);
    Component();
    virtual ~Component(){}
};

#endif // COMPONENT_H
