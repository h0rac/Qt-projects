#ifndef MAPPER_H
#define MAPPER_H
#include <QSignalMapper>
#include <QDebug>
#include <QAction>
#include <gui/gnetdevice.h>

#include <QObject>

class GNetDevice;
class HostnameWidget;

class Mapper : public QObject
{
    Q_OBJECT


    GNetDevice *gdev;
    uint presscount;
    QString srcIntf;
    QString dstIntf;
    HostnameWidget * chostwidget;

public:
    explicit Mapper(QObject *parent = 0);
    void setGnetDevPtr(GNetDevice * dev);


signals:

public slots:
    void deviceClicked(int id);
    void menuItemClicked(int id);
    void test();
};

#endif // MAPPER_H
