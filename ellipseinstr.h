#ifndef ELLIPSEINSTR_H
#define ELLIPSEINSTR_H

#include "commoninstr.h"

class EllipseInstr : public CommonInstr
{
    Q_OBJECT
public:
    explicit EllipseInstr(QWidget *parent = 0);
    void mousePress(QMouseEvent*);
    void mouseMove(QMouseEvent *);
    void mouseRelease(QMouseEvent*);
signals:

public slots:

protected:
    void use();
};

#endif // ELLIPSEINSTR_H
