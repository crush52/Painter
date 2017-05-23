#ifndef RECTANGLEINSTR_H
#define RECTANGLEINSTR_H

#include "commoninstr.h"
//class CommonInstr;

class RectangleInstr : public CommonInstr
{
    Q_OBJECT
public:
    explicit RectangleInstr(QWidget *parent = 0);
    void mousePress(QMouseEvent*);
    void mouseMove(QMouseEvent *);
    void mouseRelease(QMouseEvent*);
signals:

public slots:

protected:
    void use();
};

#endif // RECTANGLEINSTR_H
