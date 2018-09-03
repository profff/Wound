#ifndef WINDINGS_H
#define WINDINGS_H

#include <QWidget>

#define SWITCH_COIL_DIR(dir) {if(dir==up)dir=down;else dir=up;}

class Windings : public QWidget
{
    Q_OBJECT
public:
    explicit Windings(QWidget *parent = nullptr);

    enum WindingType{
        wt_regular,
        wt_interlaced,
        wt_diametral,
    };
    enum PhaseCoilType{
        pt_chain,
        pt_parallel,
    };
    enum BeamDir{
        bd_up,
        bd_down,
    };
    enum CoilType{
        ct_regular,
        ct_Concentric,
    };
    int SlotCount() const { return m_SlotCount; }
    int PhaseCount() const { return m_PhaseCount; }
    int PoleCount() const { return m_PoleCount; }
    int PolarStep() const { return m_PoleCount; }

signals:

public slots:
    void setSlotCount(int val);
    void setPhaseCount(int val);
    void setPoleCount(int val);
    void setWindingType(int val);
    void setCoilType(int val);
    void setPhaseCoilType(int val);

protected:
    int m_PhaseCount;
    int m_PoleCount;
    int m_SlotCount;

    WindingType m_WindingType;
    PhaseCoilType m_PhType;
    CoilType m_ClType;

    int m_CoilGroupCount;
    int m_SlotPerPhaseCount;
    int m_SlotPerCoilGroupCount;
    int m_SlotPerCoilCount;
    int m_SlotPerPoleCount;

    int m_PolarStep;
    int m_BeamPerPole;

    struct BeamDesc{
        int PhaseIdx;
        int PoleIdx;
        BeamDir Dir;
        int Idx;
        int NextBeamIdx;
        int NextBeamLayer;
    };

    struct CoilDesc{
        int StartSlotIdx;
        int StartLayerIdx;
        int StopSlotIdx;
        int StopLayerIdx;
        int PhaseIdx;
        CoilType Type;
    };

    struct PhaseDesc{
        QList <CoilDesc> Coils;
        int StartSlotIdx;
        int StartLayerIdx;
        int StopSlotIdx;
        int StopLayerIdx;
    };

    QList <PhaseDesc> Phases;

    struct SlotDesc{
        QList <BeamDesc> Beams;
    };

    QList <SlotDesc> Slots;
    void ClearDatas();
    void CalcWinding();
    void CalcWindingRegular();
    QColor BeamColor(BeamDesc b);

};

#endif // WINDINGS_H
