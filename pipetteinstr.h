#ifndef PIPETTEINSTR_H
#define PIPETTEINSTR_H
#include "commoninstr.h"


class PipetteInstr : public CommonInstr
{
    Q_OBJECT

public:
    explicit PipetteInstr(QWidget *parent = 0);
    void mousePress(QMouseEvent*);
    void mouseMove(QMouseEvent *);
    void mouseRelease(QMouseEvent*);
protected:
    void use();
};
#endif // PIPETTEINSTR_H
