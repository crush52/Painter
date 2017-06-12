#include "pencilinstr.h"
#include <QPainter>
#include <QDebug>

PencilInstr::PencilInstr(QWidget *parent) : CommonInstr(parent)
{
    imageArea = dynamic_cast<ImageArea*>(parent);
}

void PencilInstr::mousePress(QMouseEvent *me)
{
    start = end = me->pos()/imageArea->getScaledFactor();
}

void PencilInstr::mouseMove(QMouseEvent *me)
{
    end = me->pos()/imageArea->getScaledFactor();
    use();
    start = end;
}

void PencilInstr::mouseRelease(QMouseEvent *me)
{
    if(start == end) return;
    imageArea->setChangeFlag(false);
}

void PencilInstr::use()
{
    imageArea->setChangeFlag(true);
    QPainter painter(imageArea->getPartOfImage());
    painter.setRenderHint(QPainter::Antialiasing,imageArea->isAntialiasing());
    painter.setPen(QPen(imageArea->getPen().color()));
    painter.drawLine(QLine(start,end));
    painter.end();
    imageArea->update();
}
