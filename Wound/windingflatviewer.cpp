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
    while( i < m_SlotCount)
    {
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
            if(B.Dir==bd_up){
                int beamx        =sector*i+j+1; // +1 to shift from box edge +j to shift when different layers
                int beamtopstart    =-5+7*j; // 7 between layers (5 for box 2for spacing)
                int beamtopstop     =-10+7*j // 5 mini
                                     -B.Idx*2 // shift for each beam the top
                                     -B.PhaseIdx*(3+m_BeamPerPole*2);// shift phases 3+ 2 for each beam
                painter.drawLine(beamx,beamtopstart,beamx,beamtopstop); //up line
                painter.drawLine(beamx,5+7*j,beamx,10+7*j+(B.Idx-1)*2+B.PhaseIdx*(3+m_BeamPerPole*2)); // down line
                int ni=B.NextBeamIdx;
                int nj=B.NextBeamLayer;
                if(ni>0) // test about layer also ###
                {
                    int offset=0;
                    if(ni<i)
                    {
                       offset=m_SlotCount;
                       painter.drawLine(sector*(ni)+nj*1+1,-10+7*nj-B.Idx*2-B.PhaseIdx*(3+m_BeamPerPole*2),
                                     sector*(i-offset)+j*1+1,-10+7*j-B.Idx*2-B.PhaseIdx*(3+m_BeamPerPole*2));
                    }
                    painter.drawLine(sector*(ni+offset)+nj*1+1,-10+7*nj-B.Idx*2-B.PhaseIdx*(3+m_BeamPerPole*2),
                                     sector*i+j*1+1,-10+7*j-B.Idx*2-B.PhaseIdx*(3+m_BeamPerPole*2));

                }
            }
            else{
                painter.drawLine(sector*i+j*1+1,-5+7*j,sector*i+j*1+1,-10+7*j-B.Idx*2-B.PhaseIdx*(3+m_BeamPerPole*2));
                painter.drawLine(sector*i+j*1+1,5+7*j,sector*i+j*1+1,10+7*j+B.Idx*2+B.PhaseIdx*(3+m_BeamPerPole*2));
                int ni=B.NextBeamIdx;
                int nj=B.NextBeamLayer;
                if(ni>=0) // test about layer also ###
                {
                    int offset=0;
                    if(ni>i)
                    {
                        offset=m_SlotCount;
                        painter.drawLine(sector*(ni)+nj*1+1,10+7*nj+B.Idx*2+B.PhaseIdx*(3+m_BeamPerPole*2),
                                         sector*(i+offset)+j*1+1,10+7*j+B.Idx*2+B.PhaseIdx*(3+m_BeamPerPole*2));

                    }
                    painter.drawLine(sector*(ni-offset)+nj*1+1,10+7*nj+B.Idx*2+B.PhaseIdx*(3+m_BeamPerPole*2),
                                     sector*i+j*1+1,10+7*j+B.Idx*2+B.PhaseIdx*(3+m_BeamPerPole*2));
                }
            }
            j++;
        }
        i++;
    }
    // start / end coils / phases
//    i=0;
//    while(i<Phases.count())
//    {
//        int j=0;
//        while(j<Phases[i].Coils.count()){
//            CoilDesc c=Phases[i].Coils[j];
//            if(Slots[c.StartSlotIdx].Beams.count()==0||Slots[c.StopSlotIdx].Beams.count()==0)
//                break;
//            BeamDesc bi=Slots[c.StartSlotIdx].Beams[c.StartLayerIdx];
//            BeamDesc bo=Slots[c.StopSlotIdx].Beams[c.StopLayerIdx];

//            painter.setPen(Windings::BeamColor(bi));
//            painter.drawLine(sector*c.StartSlotIdx+c.StartLayerIdx*1+1, 10+7*c.StartLayerIdx,
//                             sector*c.StartSlotIdx+c.StartLayerIdx*1+1, 25+7*c.StartLayerIdx+5*(i));
//            painter.setPen(Windings::BeamColor(bo));
//            painter.drawLine(sector*c.StopSlotIdx+c.StopLayerIdx*1+1, 10+7*c.StopLayerIdx,
//                             sector*c.StopSlotIdx+c.StopLayerIdx*1+1, 25+7*c.StopLayerIdx+5*(i));
//            j++;
//        }

//        j=0;
//        while(j<Phases[i].Coils.count()-1){
//            CoilDesc c1=Phases[i].Coils[j];
//            CoilDesc c2=Phases[i].Coils[j+1];
//            if(Slots[c2.StartSlotIdx].Beams.count()==0||Slots[c1.StopSlotIdx].Beams.count()==0)
//                break;

//            BeamDesc bo=Slots[c1.StopSlotIdx].Beams[c1.StopLayerIdx];

//            painter.setPen(Windings::BeamColor(bo));
//            if(c1.StopSlotIdx<c2.StartSlotIdx)
//                painter.drawLine(sector*c1.StopSlotIdx+c1.StopLayerIdx*1+1, 25+7*c1.StopLayerIdx+5*(i),
//                                 sector*c2.StartSlotIdx+c2.StartLayerIdx*1+1, 25+7*c2.StartLayerIdx+5*(i));
//            else
//            {
//                int in=c2.StartSlotIdx+m_SlotCount;
//                int out=c1.StopSlotIdx;
//                painter.drawLine(sector*out+c1.StopLayerIdx*1+1, 25+7*c1.StopLayerIdx+5*(i),
//                                 sector*in+c2.StartLayerIdx*1+1, 25+7*c2.StartLayerIdx+5*(i));
//                in=c2.StartSlotIdx;
//                out=c1.StopSlotIdx-m_SlotCount;
//                painter.drawLine(sector*out+c1.StopLayerIdx*1+1, 25+7*c1.StopLayerIdx+5*(i),
//                                 sector*in+c2.StartLayerIdx*1+1, 25+7*c2.StartLayerIdx+5*(i));
//            }
//            j++;
//        }

//        i++;
//    }

}
