#ifndef BRUSHINSTR_H
#define BRUSHINSTR_H
#include "commoninstr.h"

class BrushInstr : public CommonInstr
{
    Q_OBJECT
public:
    explicit BrushInstr(QWidget *parent = 0);
    void mousePress(QMouseEvent*);
    void mouseMove(QMouseEvent *);
    void mouseRelease(QMouseEvent*);
signals:

public slots:

protected:
    void use();
};

#endif // BRUSHINSTR_H
