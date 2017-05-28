#ifndef LINEINSTR_H
#define LINEINSTR_H
#include "commoninstr.h"

class LineInstr: public CommonInstr
{
    Q_OBJECT
public:
    explicit LineInstr(QWidget *parent = 0);
    void mousePress(QMouseEvent*);
    void mouseMove(QMouseEvent *);
    void mouseRelease(QMouseEvent*);
signals:

public slots:

protected:
    void use();
};

#endif // LINEINSTR_H
