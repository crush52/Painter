#ifndef ELLIPSEINSTR_H
#define ELLIPSEINSTR_H

#include "commoninstr.h"

class EllipseInstr : public CommonInstr
{
    Q_OBJECT
public:
    explicit EllipseInstr(QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
signals:

public slots:

protected:
    void paint();
};

#endif // ELLIPSEINSTR_H
