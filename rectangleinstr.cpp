#include "rectangleinstr.h"
#include <QPainter>
#include <iostream>

RectangleInstr::RectangleInstr(QWidget *parent) : CommonInstr(parent)
{
    imageArea = dynamic_cast<ImageArea*>(parent);
}

void RectangleInstr::mousePress(QMouseEvent *me)
{
    start = end = me->pos();
}

void RectangleInstr::mouseMove(QMouseEvent *me)
{
    end = me->pos();
    use();
}

void RectangleInstr::mouseRelease(QMouseEvent *me)
{
    imageArea->setChangeFlag(false);
    imageArea->setChangeAfterFlag(true);
}

void RectangleInstr::use()
{
    imageArea->setChangeFlag(true);
    *(imageArea->getImage()) = *(imageArea->getImageCopy());
    QPainter painter(imageArea->getPartOfImage());
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(imageArea->getPen());
    painter.setBrush(imageArea->getBrush());
    painter.drawRect(QRect(start,end));
    painter.end();
    imageArea->update();

}
