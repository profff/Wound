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

    int m_BeamPerPole;



    enum BeamDir{
        up,
        down,
    };

    struct BeamDesc{
        int PhaseIdx;
        int PoleIdx;
        BeamDir Dir;
        int NextBeamIdx;
        int NextBeamLayer;
    };
    enum CoilType{
        Equal,
        Concentric,
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
    QColor BeamColor(BeamDesc b);

};

#endif // WINDINGS_H
