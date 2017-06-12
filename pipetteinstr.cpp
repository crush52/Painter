#include "pipetteinstr.h"
#include <QPainter>

PipetteInstr::PipetteInstr(QWidget *parent) : CommonInstr(parent)
{
    imageArea = dynamic_cast<ImageArea*>(parent);
}

void PipetteInstr::mousePress(QMouseEvent *me)
{
    start = end = me->pos()/imageArea->getScaledFactor();
    use();
}

void PipetteInstr::mouseMove(QMouseEvent *me){}

void PipetteInstr::mouseRelease(QMouseEvent *me){}

void PipetteInstr::use()
{
    imageArea->setColor_(QColor(imageArea->getImage()->pixel(start)).name());
}
