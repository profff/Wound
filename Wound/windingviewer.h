#ifndef WINDINGVIEWER_H
#define WINDINGVIEWER_H

#include "windings.h"

class WindingViewer : public Windings
{
    Q_OBJECT
public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    QSizePolicy sizePolicy() const;
    enum TypeView{
        frontView,
        backView,
    };
    TypeView View() const {return m_View;}

public slots:
    void setView(TypeView val);
protected:
    void paintEvent(QPaintEvent *event) override;
    TypeView m_View;
signals:
};

#endif // WINDINGVIEWER_H
