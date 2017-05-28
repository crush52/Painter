#include "lineinstr.h"
#include <QPainter>

LineInstr::LineInstr(QWidget *parent) : CommonInstr(parent)
{
    imageArea = dynamic_cast<ImageArea*>(parent);
}

void LineInstr::mousePress(QMouseEvent *me)
{
    start = end = me->pos();
}

void LineInstr::mouseMove(QMouseEvent *me)
{
    end = me->pos();
    use();
}

void LineInstr::mouseRelease(QMouseEvent *me)
{
    if(start == end) return;
    imageArea->setChangeFlag(false);
    imageArea->setChangeAfterFlag(true);
}

void LineInstr::use()
{
    imageArea->setChangeFlag(true);
    *(imageArea->getImage()) = *(imageArea->getImageCopy());
    QPainter painter(imageArea->getPartOfImage());
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(imageArea->getPen());
    painter.setBrush(imageArea->getBrush());
    painter.drawLine(QLine(start,end));
    painter.end();
    imageArea->update();
}
