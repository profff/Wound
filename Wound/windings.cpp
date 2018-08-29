#include "windings.h"

Windings::Windings(QWidget *parent) : QWidget(parent)
{
    m_PhaseCount=3;
    m_SlotCount=3;
    m_PoleCount=2;
    m_WindingType=wt_wavy;

    Layers.clear();
    int i=0; slotconfig* scu;
    while(i<m_SlotCount*2)
    {
        scu=(slotconfig*)malloc(sizeof(slotconfig));
        Layers.append(scu);
        scu->Id=i%m_SlotCount;
        i++;
    }

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
    default : R=200; V=200; B=200; break;
    }
    return QColor(R,V,B);
}

void Windings::calculate()
{
    m_PolarStep=m_SlotCount/m_PoleCount;
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
    m_SlotPerPhaseCount=m_SlotCount/m_PhaseCount;
    m_SlotPerPoleCount=m_SlotPerPhaseCount/m_PoleCount;
    m_SlotPerCoilGroupCount=m_SlotPerPhaseCount/m_CoilGroupCount;
    m_SlotPerCoilCount=m_SlotPerCoilGroupCount/2;


    Layers.clear();
    int i=0; slotconfig* scu;
    while(i<m_SlotCount*2)
    {
        scu=(slotconfig*)malloc(sizeof(slotconfig));
        Layers.append(scu);
        scu->Id=i;
        scu->CoilDirection=down;
        scu->Phase=-1;
        scu->PoleNumber=-1;
        scu->prevslot=0;
        scu->nextslot=0;
        scu->tag=SLOT_STANDARD;
        i++;
    }

    int slot =0; coildirection dir=up;
    slotconfig* prevslot=0;
    int ph=0;
    while(ph < m_PhaseCount)
    {
        slot=ph*(m_SlotCount/m_PhaseCount); // start coil is shifted of pole slot count
        prevslot=0;
        int pl=0;
        while(pl<m_PoleCount)
        {
            prevslot=0;
            slotconfig* scu;
            slotconfig* scd;
            int cl=0;
            while(cl<m_SlotPerPoleCount)
            {
                scu=Layers[(slot+cl)%m_SlotCount];
                scu->Phase=ph;
                scu->CoilDirection=dir;
                scu->PoleNumber=pl;
                scu->prevslot=prevslot;
                if(prevslot)
                    prevslot->nextslot=scu;
                prevslot=scu;
                if(cl==0)
                {
                    if(dir==up)
                    {
                        scu->tag+=SLOT_IN_COIL;
                        if(pl==0)
                            scu->tag+=SLOT_IN_PHASE;
                    }
                }
                SWITCH_COIL_DIR(dir);
                scd=Layers[(slot+cl+m_PolarStep)%m_SlotCount];
                scd->Phase=ph;
                scd->CoilDirection=dir;
                scd->PoleNumber=pl;
                scd->prevslot=prevslot;
                if(prevslot)
                    prevslot->nextslot=scd;
                prevslot=scd;
                if(cl==m_SlotPerPoleCount-1)
                {
                    if(dir==down)
                    {
                        scd->tag+=SLOT_OUT_COIL;
                        if(pl==m_PoleCount-1)
                            scd->tag+=SLOT_OUT_PHASE;
                    }
                }
                SWITCH_COIL_DIR(dir);
                cl++;
            }
            if(prevslot)
                prevslot->nextslot=scd;
//            if(dir==up)
//                dir=down;
//            else
//                dir=up;
            slot+=(m_PolarStep*2);
            slot%=m_SlotCount;
            pl+=2;//1 coil=2 poles

        }
        ph++;
    }
}
