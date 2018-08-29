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
    painter.setFont(QFont("verdana",3));
    QFontMetrics fm=painter.fontMetrics();
    qreal sector=factor/(m_SlotCount);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(0, height() / 2);
    painter.scale(side / factor, side / factor);
    int xtrans=0;
    for (int i = 0; i < m_SlotCount; ++i) {
        xtrans=sector*i;
        painter.setPen(BorderSlotColor);
        QColor SlotColor=Windings::SlotColor(Layers[i]);
        painter.setBrush(SlotColor);
        painter.drawRoundRect(QRect(QPoint(sector*Layers[i]->Id,-4),
                                    QPoint(sector*Layers[i]->Id+sector/2,0)
                                    ),5); // ext layer
        painter.setPen(SlotColor);
        if(Layers[i]->CoilDirection==up)
        {
            painter.drawLine(QPoint(sector*Layers[i]->Id+1,-10),
                             QPoint(sector*Layers[i]->Id+1,-20)); // line up
            painter.drawLine(QPoint(sector*Layers[i]->Id+1,10),
                             QPoint(sector*Layers[i]->Id+1,50)); // line down
            if(Layers[i]->nextslot && (Layers[i]->nextslot->Id>i))
                painter.drawLine(QPoint(sector*Layers[i]->Id+1,-20),
                                 QPoint(sector*Layers[i]->nextslot->Id+1,-50)); // diag line to next slot of coil
        }
        if(Layers[i]->CoilDirection==down)
        {
            painter.drawLine(QPoint(sector*Layers[i]->Id+1,-10),
                             QPoint(sector*Layers[i]->Id+1,-50)); // line up
            painter.drawLine(QPoint(sector*Layers[i]->Id+1,10),
                             QPoint(sector*Layers[i]->Id+1,20)); // line down
            if(Layers[i]->prevslot && (Layers[i]->prevslot->Id<i))
                painter.drawLine(QPoint(sector*Layers[i]->Id+1,20),
                                 QPoint(sector*Layers[i]->prevslot->Id+1,50)); // diag line to prev slot of coil
        }
        //        if(Layers[i]->tag&SLOT_IN_COIL)
//        {
//            painter.drawLine(QPoint(sector/3,10),QPoint(sector/3,20));
//        }
//        if(Layers[i]->tag&SLOT_OUT_COIL)
//        {
//            painter.drawLine(QPoint(sector/3,10),QPoint(sector/3,20));
//        }
//        painter.setBrush(Windings::SlotColor(Layers[i+m_SlotCount]));
//        painter.drawRoundRect(QRect(QPoint(0+xtrans,2),QPoint(sector+xtrans,5)),5); // int layer
        painter.setPen(QColor(0,0,0));
        painter.drawText(QPoint(0+xtrans,-fm.height()-1.5), QString::number(i));
        //painter.translate(sector*2,0);
    }
}
