#ifndef RECTANGLEINSTR_H
#define RECTANGLEINSTR_H

#include "commoninstr.h"
class CommonInstr;

class RectangleInstr : public CommonInstr
{
    Q_OBJECT
public:
    explicit RectangleInstr(QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
signals:

public slots:

protected:
    void paint();
};

#endif // RECTANGLEINSTR_H
