#ifndef GPACKET_H
#define GPACKET_H
#include <QGraphicsRectItem>
#include <QTimer>


class GPacket : QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    GPacket();
};

#endif // GPACKET_H
