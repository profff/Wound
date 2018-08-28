#ifndef WINDINGS_H
#define WINDINGS_H

#include <QWidget>

class Windings : public QWidget
{
    Q_OBJECT
public:
    explicit Windings(QWidget *parent = nullptr);
    int SlotCount() const { return m_SlotCount; }
    int PhaseCount() const { return m_PhaseCount; }
    int PoleCount() const { return m_PoleCount; }
    int PolarStep() const { return m_PoleCount; }
    int CoilGroupCount() const {return m_CoilGroupCount;}
    int SlotPerPhaseCount() const {return m_SlotPerPhaseCount;}
    int SlotPreCoilGroupCount() const {return m_SlotPerCoilGroupCount;}
    int SlotPreCoilCount() const {return m_SlotPerCoilCount;}
    int WindingType() const {return m_WindingType;}

signals:
    void PolarStepChanged(int newValue);
    void CoilGroupCountChanged(int newValue);
    void SlotPerPhaseCountChanged(int newValue);
    void SlotPerCoildGroupCounthanged(int newValue);
    void SlotPerCoilCountChanged(int newValue);

public slots:
    void setSlotCount(int val);
    void setPhaseCount(int val);
    void setPoleCount(int val);
    void setWindingType(int val);

protected:
    int m_PhaseCount;
    int m_PoleCount;
    int m_SlotCount;

    enum windingtype{
        wt_wavy,
        wt_interlaced,
        wt_diametral,
    };
    windingtype m_WindingType;

    int m_PolarStep;
    int m_CoilGroupCount;
    int m_SlotPerPhaseCount;
    int m_SlotPerCoilGroupCount;
    int m_SlotPerCoilCount;

    enum coildirection{
        up,
        down,
    };

    struct slotconfig{
        int Id;
        int Phase;
        coildirection CoilDirection;
        int PoleNumber;
    };

    QList <slotconfig*> ExtLayer;
    QList <slotconfig*> IntLayer;

    void calculate();
    QColor SlotColor(slotconfig s):

};

#endif // WINDINGS_H
