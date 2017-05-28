#include "pencilinstr.h"
#include <QPainter>
#include <QDebug>

PencilInstr::PencilInstr(QWidget *parent) : CommonInstr(parent)
{
    imageArea = dynamic_cast<ImageArea*>(parent);
}

void PencilInstr::mousePress(QMouseEvent *me)
{
    start = end = me->pos();
}

void PencilInstr::mouseMove(QMouseEvent *me)
{
    end = me->pos();
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
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(imageArea->getPen().color()));
//    painter.setBrush(imageArea->getBrush());
    painter.drawLine(QLine(start,end));
    painter.end();
    imageArea->update();
}
