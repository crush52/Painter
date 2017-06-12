#ifndef CUTINSTR_H
#define CUTINSTR_H
#include "commoninstr.h"

class CutInstr : public CommonInstr
{
    Q_OBJECT
public:
    explicit CutInstr(QWidget *parent = 0);
    void mousePress(QMouseEvent*);
    void mouseMove(QMouseEvent *);
    void mouseRelease(QMouseEvent*);
    void setFlags(bool);
    void setFirstClick(bool);
signals:

public slots:

protected:
    void use();
private:
    void moveFragment(QPoint);
    bool isAllocated,isFirstClick;
    QPoint click;
};

#endif // CUTINSTR_H
