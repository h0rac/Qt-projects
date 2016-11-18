#ifndef ENTITY_H
#define ENTITY_H
#include <QtGlobal>
#include <QString>

class Entity
{
private:
    uint m_id;
    QString m_name;

public:
    Entity(uint id);
    uint getID();
    QString getName();
};

#endif // ENTITY_H
