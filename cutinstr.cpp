#include "cutinstr.h"
#include <QPainter>
#include <algorithm>
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
        QPainter painter(imageArea->getImage());
        painter.fillRect(QRect(start,end),Qt::white);
        painter.end();
        *(imageArea->getImageCopy()) = *(imageArea->getImage());
        isFirstClick = false;
    }
    if(isAllocated)
    {
        click = me->pos()/imageArea->getScaledFactor();
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
        imageArea->setCursor(Qt::OpenHandCursor);
        moveFragment(me->pos()/imageArea->getScaledFactor());
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
    if(isFirstClick)
    {
        QPoint tmp = QPoint(std::min(start.x(),end.x()),std::min(start.y(),end.y()));
        end = QPoint(std::max(start.x(),end.x()),std::max(start.y(),end.y()));
        start = tmp;
        *(imageArea->getPartOfImage()) = imageArea->getImage()->copy(QRect(start,end));
    }
    imageArea->setChangeFlag(false);
    imageArea->setCursor(Qt::ArrowCursor);
}

void CutInstr::setFlags(bool flag)
{
    isAllocated = flag;
    isFirstClick = flag;
}

void CutInstr::setFirstClick(bool flag)
{
    isFirstClick = flag;
}

void CutInstr::use()
{
    imageArea->setSelect(true);
    imageArea->update();
}

void CutInstr::moveFragment(QPoint mousePoint)
{
    imageArea->setChangeFlag(true);
    *(imageArea->getImage()) = *(imageArea->getImageCopy());
    start = start + mousePoint - click;
    end = end + mousePoint - click;
    click = mousePoint;
    return;
}
