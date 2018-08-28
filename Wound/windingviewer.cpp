#include "windingviewer.h"
#include "qpainter.h"
#include <QtMath>

QSize WindingViewer::sizeHint() const
{
    return QSize(200, 200);
}
QSize WindingViewer::minimumSizeHint() const
{
    return QSize(200, 200);
}
QSizePolicy WindingViewer::sizePolicy() const
{
    return QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
}

void WindingViewer::setView(TypeView val)
{
    m_View=val;
    repaint();
}

void WindingViewer::paintEvent(QPaintEvent *)
{

    int side = qMin(width(), height());
    QColor SlotColor(127, 127, 127);
    QPainter painter(this);

    painter.setPen(SlotColor);
    painter.setBrush(QColor(255,127,127));
    painter.setFont(QFont("verdana",5));
    QFontMetrics fm=painter.fontMetrics();
    qreal sector=360.0/m_SlotCount;
    int topPty=qSin(qDegreesToRadians((sector-sector/10)/2))*95;
    int midPty=qSin(qDegreesToRadians((sector-sector/10)/2))*85;
    int botPty=qSin(qDegreesToRadians((sector-sector/10)/2))*75;
    int topPtx=qCos(qDegreesToRadians((sector-sector/10)/2))*95;
    int midPtx=qCos(qDegreesToRadians((sector-sector/10)/2))*85;
    int botPtx=qCos(qDegreesToRadians((sector-sector/10)/2))*75;
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);

    switch(m_View)
    {
        case frontView:
            painter.drawText(-95,-95,"Front");
        break;
        case backView:
            painter.drawText(-95,-95,"Back");
        break;
    }


    QPainterPath extPath;
    extPath.moveTo(topPtx,topPty);
    extPath.lineTo(topPtx,-topPty);
    extPath.lineTo(midPtx,-midPty);
    extPath.lineTo(midPtx,midPty);
    extPath.lineTo(topPtx,topPty);
    QPainterPath intPath;
    intPath.moveTo(midPtx,midPty);
    intPath.lineTo(midPtx,-midPty);
    intPath.lineTo(botPtx,-botPty);
    intPath.lineTo(botPtx,botPty);
    intPath.lineTo(midPtx,midPty);

    for (int i = 0; i < m_SlotCount; ++i) {
//        painter.drawLine(botPtx,botPty,topPtx,topPty);
//        painter.drawLine(botPtx,-botPty,topPtx,-topPty);
//        painter.drawLine(botPtx,-botPty,botPtx,botPty);
//        painter.drawLine(midPtx,-midPty,midPtx,midPty);
//        painter.drawLine(topPtx,-topPty,topPtx,topPty);
        painter.drawPath(extPath);
        painter.drawPath(intPath);
        painter.drawText(qCos(qDegreesToRadians((sector-sector/10)/2))*65,
                         0+fm.height()/2,//qSin(qDegreesToRadians((sector-sector/10)/2))*65,
                         QString::number(i));

        painter.rotate(sector);
    }
}
