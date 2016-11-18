#ifndef BPDU_H
#define BPDU_H
#include <core/packet/packet.h>
#include <QtGlobal>
#include <QBitArray>

class Bpdu: public Packet
{
public:
    Bpdu();

    quint16 proto_id;
    quint8 version;
    quint8 msgtype;
    quint8 flags_tca:1;
    quint8 flags_agr:1;
    quint8 flags_fwd:1;
    quint8 flags_lrn:1;
    quint8 flags_role:2;
    quint8 flags_proposal:1;
    quint8 flags_tc:1;
    quint8 rootBidPrio:4;
    quint32 rootBSID:12;
    quint64 rootMAC:48;
    quint32 rootPcost;
    quint8 bridgeIdPrio:4;
    quint32 bridgeSID:12;
    quint64 bridgeMAC:48;
    quint16 portID;
    quint16 msgAge;
    quint16 maxAge;
    quint16 helloTime;
    quint16 fwdDelay;

};

#endif // BPDU_H
