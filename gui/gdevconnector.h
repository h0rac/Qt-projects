#ifndef GDEVCONNECTOR_H
#define GDEVCONNECTOR_H


#include <QGraphicsLineItem>
#include <gui/gnetdevice.h>

class GNetDevice;

class GDevConnector: public QGraphicsLineItem
{

public:
    GDevConnector();

private:

    QPointF *psrc;
    QPointF *pdst;



public:
    void connect(GNetDevice *src, GNetDevice *dst, QString srcIntf, QString dstIntf);
    //void connect(QPointF *src, QPointF *dst);
    void drawConnection(QPointF *src, QPointF *dst);
    void drawConnection();

    QString srcInterface;
    QString dstInterface;
    GNetDevice *fromSrc;
    GNetDevice *toDst;

protected:
     //void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};


#endif // DEVCONNECTOR_H
