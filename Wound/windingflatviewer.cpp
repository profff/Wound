#include "windingflatviewer.h"
#include "qpainter.h"
#include <QtMath>

QSize WindingFlatViewer::sizeHint() const
{
    return QSize(800, 200);
}
QSize WindingFlatViewer::minimumSizeHint() const
{
    return QSize(800, 200);
}
QSizePolicy WindingFlatViewer::sizePolicy() const
{
    return QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
}


void WindingFlatViewer::paintEvent(QPaintEvent *)
{

    int side = qMax(width(), height());
    QColor BorderSlotColor(127, 127, 127);
    QPainter painter(this);
    const qreal factor=400;
    painter.setPen(BorderSlotColor);

    QFontMetrics fm=painter.fontMetrics();
    qreal sector=factor/(m_SlotCount);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(0, height() / 2);
    painter.scale(side / factor, side / factor);

    int i = 0;
    while( i < m_SlotCount) {
        painter.setPen(BorderSlotColor);
        painter.setFont(QFont("verdana",3));
        painter.drawText(sector*i,-1.5,QString::number(i));
        int j=0;
        while(j<Slots[i].Beams.count()){
            BeamDesc B=Slots[i].Beams[j];
            painter.setPen(BorderSlotColor);
            painter.setBrush(Windings::BeamColor(B));
            painter.drawRoundRect(sector*i+j*1,7*j,5,5,1,1); // ext layer
            painter.setPen(Windings::BeamColor(B));
            if(B.Dir==up){
                painter.drawLine(sector*i+j*1+1,-5+7*j,sector*i+j*1+1,-10+7*j);
                painter.drawLine(sector*i+j*1+1,5+7*j,sector*i+j*1+1,20+7*j);
                int ni=B.NextBeamIdx;
                int nj=B.NextBeamLayer;
                if(ni>0) // test about layer also ###
                {
                    int offset=0;
                    if(ni<i)
                       offset=m_SlotCount;
                    painter.drawLine(sector*(ni+offset)+nj*1+1,-20+7*nj,
                                     sector*i+j*1+1,-10+7*j);
                    painter.drawLine(sector*(ni)+nj*1+1,-20+7*nj,
                                     sector*(i-offset)+j*1+1,-10+7*j);
                }
            }
            else{
                painter.drawLine(sector*i+j*1+1,-5+7*j,sector*i+j*1+1,-20+7*j);
                painter.drawLine(sector*i+j*1+1,5+7*j,sector*i+j*1+1,10+7*j);
                int ni=B.NextBeamIdx;
                int nj=B.NextBeamLayer;
                if(ni>0) // test about layer also ###
                {
                    int offset=0;
                    if(ni>i)
                        offset=m_SlotCount;
                    painter.drawLine(sector*(ni-offset)+nj*1+1,20+7*nj,
                                     sector*i+j*1+1,10+7*j);
                    painter.drawLine(sector*(ni)+nj*1+1,20+7*nj,
                                     sector*(i+offset)+j*1+1,10+7*j);
                }
            }


            j++;
        }
        i++;
    }
//        painter.setPen(SlotColor);
//        if(Layers[i]->CoilDirection==up)
//        {
//            painter.drawLine(QPoint(sector*Layers[i]->Id+1,-10),
//                             QPoint(sector*Layers[i]->Id+1,-15)); // line up
//            painter.drawLine(QPoint(sector*Layers[i]->Id+1,10),
//                             QPoint(sector*Layers[i]->Id+1,30)); // line down
//            if(Layers[i]->nextslot )
//            {
//                if( (Layers[i]->nextslot->Id>i))
//                    painter.drawLine(QPoint(sector*Layers[i]->Id+1,-15),
//                                    QPoint(sector*Layers[i]->nextslot->Id+1,-30)); // diag line to next slot of coil
//                else
//                {
//                    painter.drawLine(QPoint(sector*Layers[i]->Id+1,-15),
//                                     QPoint(sector*(Layers[i]->nextslot->Id+m_SlotCount)+1,-30)); // diag line to next slot of coil
//                    painter.drawLine(QPoint(sector*(Layers[i]->Id-m_SlotCount)+1,-15),
//                                     QPoint(sector*(Layers[i]->nextslot->Id)+1,-30)); // diag line to next slot of coil
//                }
//            }
//            if(Layers[i]->tag & SLOT_IN_COIL)
//            {
//                painter.drawLine(QPoint(sector*Layers[i]->Id+1,10),
//                                 QPoint(sector*Layers[i]->Id+1,35+5*Layers[i]->Phase)); // line down
//                painter.setPen(QColor(0,0,0));
//                painter.drawText(QPoint(sector*Layers[i]->Id+2,35+5*Layers[i]->Phase), "in");
//            }
//        }
//        if(Layers[i]->CoilDirection==down)
//        {
//            painter.drawLine(QPoint(sector*Layers[i]->Id+1,-10),
//                             QPoint(sector*Layers[i]->Id+1,-30)); // line up
//            painter.drawLine(QPoint(sector*Layers[i]->Id+1,10),
//                             QPoint(sector*Layers[i]->Id+1,15)); // line down
//            if(Layers[i]->tag & SLOT_OUT_COIL)
//            {
//                painter.drawLine(QPoint(sector*Layers[i]->Id+1,10),
//                                 QPoint(sector*Layers[i]->Id+1,35+5*Layers[i]->Phase)); // line down
//                painter.setPen(QColor(0,0,0));
//                painter.drawText(QPoint(sector*Layers[i]->Id+2,35+5*Layers[i]->Phase), "out");
//                if(Layers[i]->nextslot)
//                {
//                    if((Layers[i]->nextslot->Id<i))
//                        painter.drawLine(QPoint(sector*Layers[i]->Id+1,35+5*Layers[i]->Phase),
//                                         QPoint(sector*Layers[i]->nextslot->Id+1,35+5*Layers[i]->Phase)); // diag line to prev slot of coil
////                    else
////                    {
////                        painter.drawLine(QPoint(sector*Layers[i]->Id+1,15),
////                                         QPoint(sector*(Layers[i]->nextslot->Id-m_SlotCount)+1,30)); // diag line to next slot of coil
////                        painter.drawLine(QPoint(sector*(Layers[i]->Id+m_SlotCount)+1,15),
////                                         QPoint(sector*(Layers[i]->nextslot->Id)+1,30)); // diag line to next slot of coil
////                    }
//                }
//            }
//            else
//            {
//                if(Layers[i]->nextslot)
//                {
//                    if((Layers[i]->nextslot->Id<i))
//                        painter.drawLine(QPoint(sector*Layers[i]->Id+1,15),
//                                         QPoint(sector*Layers[i]->nextslot->Id+1,30)); // diag line to prev slot of coil
//                    else
//                    {
//                        painter.drawLine(QPoint(sector*Layers[i]->Id+1,15),
//                                         QPoint(sector*(Layers[i]->nextslot->Id-m_SlotCount)+1,30)); // diag line to next slot of coil
//                        painter.drawLine(QPoint(sector*(Layers[i]->Id+m_SlotCount)+1,15),
//                                         QPoint(sector*(Layers[i]->nextslot->Id)+1,30)); // diag line to next slot of coil
//                    }
//                }
//            }
//        }
////        painter.setBrush(Windings::SlotColor(Layers[i+m_SlotCount]));
////        painter.drawRoundRect(QRect(QPoint(0+xtrans,2),QPoint(sector+xtrans,5)),5); // int layer
//        painter.setPen(QColor(0,0,0));painter.setFont(QFont("verdana",3));
//        painter.drawText(QPoint(0+xtrans,-5), QString::number(i));
//        //painter.translate(sector*2,0);
//    }
}
