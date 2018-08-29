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
    QColor SlotColor(127, 127, 127);
    QPainter painter(this);
    const qreal factor=400;
    painter.setPen(SlotColor);
    painter.setFont(QFont("verdana",3));
    QFontMetrics fm=painter.fontMetrics();
    qreal sector=factor/(m_SlotCount*2);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(0, height() / 2);
    painter.scale(side / factor, side / factor);

    for (int i = 0; i < m_SlotCount; ++i) {
        painter.drawText(QPoint(0,-fm.height()-1.5), QString::number(i));
//        if(ExtLayer[i])//if slot is filled
//            painter.setBrush(Windings::SlotColor(ExtLayer[i]));
        painter.drawRoundRect(QRect(QPoint(0,-3),QPoint(sector,-1)),5); // ext layer
//        if(IntLayer[i])//if slot is filled
//            painter.setBrush(Windings::SlotColor(ExtLayer[i]));
        painter.drawRoundRect(QRect(QPoint(0,2),QPoint(sector,4)),5); // int layer
        painter.translate(sector*2,0);
    }
}
