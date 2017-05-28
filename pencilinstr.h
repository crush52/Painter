#ifndef PENCILINSTR_H
#define PENCILINSTR_H
#include "commoninstr.h"

class PencilInstr : public CommonInstr
{
    Q_OBJECT
public:
    explicit PencilInstr(QWidget *parent = 0);
    void mousePress(QMouseEvent*);
    void mouseMove(QMouseEvent *);
    void mouseRelease(QMouseEvent*);
signals:

public slots:

protected:
    void use();
};

#endif // PENCILINSTR_H
