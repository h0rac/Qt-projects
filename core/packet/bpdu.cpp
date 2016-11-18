#include <core/packet/bpdu.h>
#include <QDebug>

Bpdu::Bpdu():Packet()
{
    proto_id = 0x0000;
    qDebug()<<"Size of proto_id"<<sizeof(proto_id);

    flags_tca = 0;
    flags_agr = 0;
    flags_fwd = 0;
    flags_lrn = 0;
    flags_role = 00;
    flags_tc = 0;
    flags_proposal = 0;

}

