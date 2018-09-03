#include "windings.h"

Windings::Windings(QWidget *parent) : QWidget(parent)
{
    m_PhaseCount=3;
    m_SlotCount=3;
    m_PoleCount=2;
    m_WindingType=wt_regular;
    m_ClType=ct_regular;
    CalcWinding();
}

// accessors
void Windings::setSlotCount(int val)
{
    if(val==m_SlotCount)
        return;
    if(val>0)
    {
        m_SlotCount=val;
        CalcWinding();
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
        CalcWinding();
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
        CalcWinding();
        repaint();
    }
}
void Windings::setWindingType(int val)
{
    if(val==(WindingType)m_WindingType)
        return;
    m_WindingType=(WindingType)val;

    CalcWinding();
    repaint();
}
void Windings::setCoilType(int val)
{
    if(val==(CoilType)m_ClType)
        return;
    m_ClType=(CoilType)val;

    CalcWinding();
    repaint();
}
void Windings::setPhaseCoilType(int val)
{
    if(val==(PhaseCoilType)m_PhType)
        return;
    m_PhType=(PhaseCoilType)val;

    CalcWinding();
    repaint();
}

void Windings::ClearDatas()
{

    // clear slot reference
    int i=0;
    while(i<Slots.count())
    {
        Slots[i].Beams.clear();
        i++;
    }
    Slots.clear();
    i=0;
    while(i<m_SlotCount)
    {
        SlotDesc S;
        Slots.append(S);
        i++;
    }

    // clear phase and coil reference
    i=0;
    while(i<Phases.count())
    {
        PhaseDesc p;
        p.Coils.clear();
        i++;
    }
    Phases.clear();
    i=0;
    while(i<m_PhaseCount)
    {
        PhaseDesc p;
        int j=0;
        while(j<m_PoleCount/2)// 1 coil = 2 poles;
        {
            CoilDesc c;
            c.PhaseIdx=i;
            p.Coils.append(c);
            j++;
        }
        Phases.append(p);
        i++;
    }

}
QColor Windings::BeamColor(BeamDesc b)
{
    int R,V,B;
    int light=0;
    if (b.Dir==bd_down)
        light+=127;
    switch (b.PhaseIdx)
    {
    case 0: R=255; V=light; B=light; break;
    case 1: R=light; V=255; B=light; break;
    case 2: R=light; V=light; B=255; break;
    default : R=200; V=200; B=200; break;
    }
    return QColor(R,V,B);
}
void Windings::CalcWinding()
{
    m_PolarStep=m_SlotCount/m_PoleCount;
    switch(m_WindingType)
    {
        case wt_interlaced:
            m_CoilGroupCount=m_PoleCount;
        break;
        case wt_regular:
        case wt_diametral:
            m_CoilGroupCount=m_PoleCount/2;
        break;
    };
    m_SlotPerPhaseCount=m_SlotCount/m_PhaseCount;
    m_SlotPerPoleCount=m_SlotPerPhaseCount/m_PoleCount;
    m_SlotPerCoilGroupCount=m_SlotPerPhaseCount/m_CoilGroupCount;
    m_SlotPerCoilCount=m_SlotPerCoilGroupCount/2;
    switch(m_WindingType)
    {
        case wt_regular:
        default:
            CalcWindingRegular();
        break;
    };

}

void Windings::CalcWindingRegular()
{

    m_BeamPerPole=m_SlotCount/(m_PoleCount*m_PhaseCount);

    ClearDatas();
    // construct slot reference
    int ph=0;
    while(ph < m_PhaseCount)
    {
        int StartSlotIdx=ph*(m_SlotCount/m_PhaseCount); // start coil is shifted of pole slot count
        Phases[ph].StartSlotIdx=StartSlotIdx;
        Phases[ph].StartLayerIdx=Slots[StartSlotIdx].Beams.count();
        int pl=0;
        while(pl<m_PoleCount) // indexing on pole but constructing coils ( 2 poles at a time)
        {
            Phases[ph].Coils[pl/2].PhaseIdx=ph;
            Phases[ph].Coils[pl/2].StartSlotIdx=(StartSlotIdx+(pl)*m_PolarStep)%m_SlotCount;
            Phases[ph].Coils[pl/2].StopSlotIdx=(StartSlotIdx+(pl+1)*m_PolarStep+m_BeamPerPole-1)%m_SlotCount;
            Phases[ph].Coils[pl/2].StartLayerIdx=Slots[Phases[ph].Coils[pl/2].StartSlotIdx].Beams.count();
            Phases[ph].Coils[pl/2].StopLayerIdx=Slots[Phases[ph].Coils[pl/2].StopSlotIdx].Beams.count();

            int bm=(m_BeamPerPole)-1;
            int nextidx=-1;
            int nextlayer=-1;

            while(bm>=0) // going backward for constructing is simpler to reference next index
            {
                int slot=(StartSlotIdx+(pl+1)*m_PolarStep+bm)%m_SlotCount;
                BeamDesc bdn;
                bdn.NextBeamIdx=nextidx;
                bdn.NextBeamLayer=nextlayer;
                bdn.Dir=bd_down;
                bdn.PhaseIdx=ph;
                bdn.PoleIdx=pl;
                bdn.Idx=bm;
                nextidx=slot;
                nextlayer=Slots[slot].Beams.count();
                Slots[slot].Beams.append(bdn);
                if(m_ClType==ct_regular)
                    slot=(StartSlotIdx+(pl)*m_PolarStep+bm)%m_SlotCount;
                else
                    slot=(StartSlotIdx+(pl)*m_PolarStep-bm+(m_BeamPerPole-1))%m_SlotCount;

                BeamDesc bup;
                bup.NextBeamIdx=nextidx;
                bup.NextBeamLayer=nextlayer;
                bup.Dir=bd_up;
                bup.PhaseIdx=ph;
                bup.PoleIdx=pl;
                bup.Idx=bm;
                nextidx=slot;
                nextlayer=Slots[slot].Beams.count();
                Slots[slot].Beams.append(bup);
                bm--;
            }
            pl+=2;//1 coil=2 poles
        }

        Phases[ph].StopSlotIdx=Phases[ph].Coils.last().StopSlotIdx;
        Phases[ph].StopLayerIdx=Phases[ph].Coils.last().StopLayerIdx;
        ph++;
    }
}
