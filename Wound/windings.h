#ifndef WINDINGS_H 
#define WINDINGS_H

#include <QWidget>

#define SWITCH_COIL_DIR(dir) {if(dir==up)dir=down;else dir=up;}

class Windings : public QWidget
{
    Q_OBJECT
public:
    explicit Windings(QWidget *parent = nullptr);
    int SlotCount() const { return m_SlotCount; }
    int PhaseCount() const { return m_PhaseCount; }
    int PoleCount() const { return m_PoleCount; }
    int PolarStep() const { return m_PoleCount; }
//    int CoilGroupCount() const {return m_CoilGroupCount;}
//    int SlotPerPhaseCount() const {return m_SlotPerPhaseCount;}
//    int SlotPreCoilGroupCount() const {return m_SlotPerCoilGroupCount;}
//    int SlotPreCoilCount() const {return m_SlotPerCoilCount;}
    int WindingType() const {return m_WindingType;}

signals:
//    void PolarStepChanged(int newValue);
//    void CoilGroupCountChanged(int newValue);
//    void SlotPerPhaseCountChanged(int newValue);
//    void SlotPerCoildGroupCounthanged(int newValue);
//    void SlotPerCoilCountChanged(int newValue);

public slots:
    void setSlotCount(int val);
    void setPhaseCount(int val);
    void setPoleCount(int val);
    void setWindingType(int val);

protected:
    int m_PhaseCount;
    int m_PoleCount;
    int m_SlotCount;
    int m_PolarStep;

    enum windingtype{
        wt_wavy,
        wt_interlaced,
        wt_diametral,
    };
    windingtype m_WindingType;

    int m_CoilGroupCount;
    int m_SlotPerPhaseCount;
    int m_SlotPerCoilGroupCount;
    int m_SlotPerCoilCount;
    int m_SlotPerPoleCount;

    enum coildirection{
        up,
        down,
    };
#define SLOT_STANDARD    0x0000
#define SLOT_IN_COIL     0x0001
#define SLOT_OUT_COIL    0x0002
#define SLOT_IN_PHASE    0x0010
#define SLOT_OUT_PHASE   0x0020
    struct slotconfig{
        int Id;
        int Phase;
        coildirection CoilDirection;
        int PoleNumber;
        slotconfig* prevslot; //-1=notset
        slotconfig* nextslot; // same
        int tag; // 0= not set -2=coil entry -3=coil exit -20=phase entry -30=phase exit
    };

    QList <slotconfig*> Layers;

    void calculate();
    QColor SlotColor(slotconfig* s);

};

#endif // WINDINGS_H
