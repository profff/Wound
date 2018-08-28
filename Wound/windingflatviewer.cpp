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
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(0, height() / 2);
    painter.scale(side/300, side / 300);
    painter.setFont(QFont("verdana",2));
    QFontMetrics fm=painter.fontMetrics();
    painter.setBrush(QColor(255,127,127));
    qreal sector=300/(m_SlotCount*2);
    for (int i = 0; i < m_SlotCount; ++i) {
        painter.setPen(SlotColor);
        painter.drawRoundRect(QRect(QPoint(sector/2,0),QPoint(sector+sector/2,fm.height())),5); // int layer
        painter.drawRoundRect(QRect(QPoint(0,-fm.height()),QPoint(sector,0)),5); // ext layer
        painter.setPen(QColor(0,0,0));
        painter.drawText(QPoint(0,0), QString::number(i));
        painter.translate(sector*2,0);
    }
}
