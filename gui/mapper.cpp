#include "mapper.h"

Mapper::Mapper(QObject *parent) : QObject(parent)
{
    presscount = 0;
}
void Mapper::setGnetDevPtr(GNetDevice *dev)
{
    gdev = dev;
}

void Mapper::deviceClicked(int id)
{
  QAction * action = dynamic_cast<QAction*>(QObject::sender()->parent());
  QString interface = action->text();

  gdev->setDataAfterClick(interface,id);
}
void Mapper::menuItemClicked(int id)
{
  QAction * action = dynamic_cast<QAction*>(QObject::sender()->parent());
  qDebug()<<"change hostname for id"<<id;
  gdev->setHostnameWidget();
}
void Mapper::test()
{
    //qDebug()<<"callback works"
    //QLineEdit * line = dynamic_cast<QLineEdit*>(QObject::sender());
   // qDebug()<<"text"<<line->text();
   // gdev->setDevHostname(line->text());

}


