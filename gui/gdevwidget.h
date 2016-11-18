#ifndef GDEVWIDGET_H
#define GDEVWIDGET_H


#include <QListWidget>
#include <gui/gnetdevice.h>
#include <QStandardItem>

class GNetDevice;

class GDevWidget: public QStandardItem
{

public:
    GDevWidget();
    GNetDevice *pdev;

};
#endif // GDEVWIDGET_H
