#include "entity.h"

Entity::Entity(uint id):m_id(id)
{

}
uint Entity::getID()
{
    return m_id;
}
QString Entity::getName()
{
    return m_name;
}

