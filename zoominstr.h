#ifndef ZOOMINSTR_H
#define ZOOMINSTR_H

#include <QAbstractItemModel>
#include "commoninstr.h"

class ZoomInstr : public CommonInstr
{
    Q_OBJECT

public:
    explicit ZoomInstr(QWidget *parent = 0);
    void mousePress(QMouseEvent*);
    void mouseMove(QMouseEvent *);
    void mouseRelease(QMouseEvent*);
protected:
    void use();


private:
    float scaledFactor;
    QSize scaledSize;
};

#endif // ZOOMINSTR_H
