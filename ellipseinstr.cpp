#include "ellipseinstr.h"
#include <QPainter>
#include <iostream>

EllipseInstr::EllipseInstr(QWidget *parent) : CommonInstr(parent)
{
    imageArea = dynamic_cast<ImageArea*>(parent);
}

void EllipseInstr::mousePress(QMouseEvent *me)
{
    start = end = me->pos();
//    use();
}

void EllipseInstr::mouseMove(QMouseEvent *me)
{
    end = me->pos();
    use();
}

void EllipseInstr::mouseRelease(QMouseEvent *me)
{
    if(start == end) return;
    imageArea->setChangeFlag(false);
    imageArea->setChangeAfterFlag(true);
}

void EllipseInstr::use()
{
    imageArea->setChangeFlag(true);
    *(imageArea->getImage()) = *(imageArea->getImageCopy());
    QPainter painter(imageArea->getPartOfImage());
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(imageArea->getPen());
    painter.setBrush(imageArea->getBrush());
    painter.drawEllipse(QRect(start,end));
    painter.end();
    imageArea->update();
}
