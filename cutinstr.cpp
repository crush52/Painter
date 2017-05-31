#include "cutinstr.h"
#include <QPainter>
#include <QDebug>

CutInstr::CutInstr(QWidget *parent) : CommonInstr(parent)
{
    imageArea = dynamic_cast<ImageArea*>(parent);
    isAllocated = false;
}

void CutInstr::mousePress(QMouseEvent *me)
{
    if(isFirstClick)
    {
        *(imageArea->getPartOfImage()) = imageArea->getImage()->copy(QRect(start,end));
        QPainter painter(imageArea->getImage());
        painter.fillRect(QRect(start,end),Qt::white);
        painter.end();
        *(imageArea->getImageCopy()) = *(imageArea->getImage());
        isFirstClick = false;
    }
    if(isAllocated)
    {
        click = me->pos();
        return;
    }
    start = end = me->pos()/imageArea->getScaledFactor();
}

void CutInstr::mouseMove(QMouseEvent *me)
{
    if(!isAllocated)
        use();
    else
    {
        moveFragment(me->pos());
        return;
    }
    end = me->pos()/imageArea->getScaledFactor();

}

void CutInstr::mouseRelease(QMouseEvent *me)
{
    if(start == end) return;
    if(!isAllocated)
    {
        isAllocated = true;
        isFirstClick = true;
    }
    imageArea->setChangeFlag(false);
}

void CutInstr::setFlags(bool)
{
    isAllocated = false;
    isFirstClick = false;
}

void CutInstr::use()
{
    imageArea->setCut(true);
    imageArea->setChangeAfterFlag(true);
    imageArea->update();
}

void CutInstr::moveFragment(QPoint mousePoint)
{
//    QPainter painter(imageArea->getImage());
    imageArea->setChangeFlag(true);
    *(imageArea->getImage()) = *(imageArea->getImageCopy());
    start = start + mousePoint - click;
    end = end + mousePoint - click;
//    qDebug() << imageArea->getPartOfImage()->width() << ' ' << imageArea->getPartOfImage()->height();
//    painter.drawImage(start,*(imageArea->getPartOfImage()),imageArea->getPartOfImage()->rect());
//    painter.end();
    click = mousePoint;
//    this->update();
    return;
}
