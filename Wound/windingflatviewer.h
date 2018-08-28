#ifndef WINDINGFLATVIEWER_H
#define WINDINGFLATVIEWER_H

#include "windings.h"

class WindingFlatViewer : public Windings
{
    Q_OBJECT
public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    QSizePolicy sizePolicy() const;

protected:
    void paintEvent(QPaintEvent *event) override;
signals:
};

#endif // WINDINGFLATVIEWER_H
