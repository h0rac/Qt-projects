#include <gui/gdevconnector.h>
#include <QPen>
#include <QDebug>

GDevConnector::GDevConnector()
{


}
void GDevConnector::connect(GNetDevice *src, GNetDevice *dst, QString srcIntf,  QString dstIntf)
{
    fromSrc = src;
    toDst = dst;
    srcInterface = srcIntf;
    dstInterface = dstIntf;


    this->setToolTip(fromSrc->hostText->toPlainText()+srcInterface+"-"+toDst->hostText->toPlainText()+dstInterface);
}
void GDevConnector::drawConnection(QPointF *src, QPointF *dst)
{

    this->setLine(src->x(),src->y(),dst->x(),dst->x());
    this->update();
}

void GDevConnector::drawConnection()
{

    QPen pen(Qt::green);
    pen.setWidth(3);
    pen.setCosmetic(true);
    this->setPen(pen);
    //qDebug()<<"fromSrc x"<<fromSrc->pos().x();
    //qDebug()<<"fromSrc y"<<fromSrc->pos().y();
    //qDebug()<<"toDst x"<<toDst->pos().x();
    //qDebug()<<"toDst y"<<toDst->pos().y();

    //qDebug()<<"Line info: fromSrc"<<fromSrc->getID();
   // qDebug()<<"Line info: toDst"<<toDst->getID();

    //this->setLine(fromSrc->pos().x()+40,fromSrc->pos().y()+30,toDst->pos().x()+40,toDst->pos().y()+30);

    this->setLine(fromSrc->pos().x()+40,fromSrc->pos().y()+30,toDst->pos().x()+40,toDst->pos().y()+30);
    this->update();
}


