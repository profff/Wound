#include "windings.h"

Windings::Windings(QWidget *parent) : QWidget(parent)
{
    m_PhaseCount=3;
    m_SlotCount=3;
    m_PoleCount=2;
    m_WindingType=wt_wavy;
    calculate();
}

// accessors
void Windings::setSlotCount(int val)
{
    if(val==m_SlotCount)
        return;
    if(val>0)
    {
        m_SlotCount=val;
        calculate();
        repaint();
    }
}
void Windings::setPhaseCount(int val)
{
    if(val==m_PhaseCount)
        return;
    if((val==3)||(val==1))
    {
        m_PhaseCount=val;
        calculate();
        repaint();
    }

}
void Windings::setPoleCount(int val)
{
    if(val==m_PoleCount)
        return;
    if(!(val%2))
    {
        m_PoleCount=val;
        calculate();
        repaint();
    }
}
void Windings::setWindingType(int val)
{
    if(val==m_WindingType)
        return;
    m_WindingType=(windingtype)val;
    calculate();
    repaint();
}

QColor Windings::SlotColor(slotconfig* s)
{
    int R,V,B;
    int light=0;
    if (s->CoilDirection==down)
        light+=127;
    switch (s->Phase)
    {
    case 0: R=255; V=light; B=light; break;
    case 1: R=light; V=255; B=light; break;
    case 2: R=light; V=light; B=255; break;
    default : R=light; V=light; B=light; break;
    }
    return QColor(R,V,B);
}

void Windings::calculate()
{
    m_PolarStep=m_SlotCount/m_PoleCount;
    emit PolarStepChanged(m_PolarStep);
    switch(m_WindingType)
    {
        case wt_interlaced:
            m_CoilGroupCount=m_PoleCount;
        break;
        case wt_wavy:
        case wt_diametral:
            m_CoilGroupCount=m_PoleCount/2;
        break;
    };
    emit CoilGroupCountChanged(m_CoilGroupCount);
    m_SlotPerPhaseCount=m_SlotCount/m_PhaseCount;
    emit SlotPerPhaseCountChanged(m_SlotPerPhaseCount);
    m_SlotPerCoilGroupCount=m_SlotPerPhaseCount/m_CoilGroupCount;
    emit SlotPerCoildGroupCounthanged(m_SlotPerCoilGroupCount);
    m_SlotPerCoilCount=m_SlotPerCoilGroupCount/2;
    emit SlotPerCoilCountChanged(m_SlotPerCoilCount);

    ExtLayer.clear();
    IntLayer.clear();

    int slot =0;
    int layer =0;
    int ph=0;
    //while(ph < m_PhaseCount)
    {
        int pl=0;
        while(pl<m_PoleCount)
        {
            int cl=0;
            while(cl<m_SlotPerCoilCount)
            {
                slotconfig* scu=new slotconfig;
                scu->Id=slot+cl;
                scu->Phase=ph;
                scu->CoilDirection=up;
                scu->PoleNumber=pl;
                if(!layer)
                    ExtLayer.insert(slot,scu);

                slotconfig *scd=new slotconfig;
                scd->Id=slot+cl+m_PolarStep;
                scd->Phase=ph;
                scd->CoilDirection=down;
                scd->PoleNumber=pl;
                if(!layer)
                    ExtLayer.insert(slot+cl+m_PolarStep,scd);

                cl++;
            }
            slot+=m_PolarStep;
            pl++;
        }
        ph++;
    }

}
