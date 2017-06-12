#include "polygonalchaininstr.h"
#include <QPainter>

PolygonalChainInstr::PolygonalChainInstr(QWidget *parent) : CommonInstr(parent)
{
    imageArea = dynamic_cast<ImageArea*>(parent);
    isFirstClick = true;
    stopDraw = false;
}

void PolygonalChainInstr::mousePress(QMouseEvent *me)
{
    if(!imageArea->isLeftButtonClicked())
    {
        stopDraw = true;
        imageArea->setMouseTracking(false);
        *(imageArea->getImage()) = *(imageArea->getImageCopy());
    }
    if(isFirstClick)
    {
        start = end = me->pos()/imageArea->getScaledFactor();
        isFirstClick = false;
        stopDraw = false;
        imageArea->setMouseTracking(true);
    }
    *(imageArea->getImageCopy()) = *(imageArea->getImage());
    start = me->pos()/imageArea->getScaledFactor();
}

void PolygonalChainInstr::mouseMove(QMouseEvent *me)
{
    if(stopDraw) return;
    end = me->pos()/imageArea->getScaledFactor();
    use();
}

void PolygonalChainInstr::mouseRelease(QMouseEvent *me)
{
    if(stopDraw)
    {
        isFirstClick = true;
        stopDraw = false;
        return;
    }
    if(start == end) return;
    imageArea->setChangeFlag(false);
}

void PolygonalChainInstr::use()
{
    imageArea->setChangeFlag(true);
    *(imageArea->getImage()) = *(imageArea->getImageCopy());
    QPainter painter(imageArea->getPartOfImage());
    painter.setRenderHint(QPainter::Antialiasing,imageArea->isAntialiasing());
    painter.setBrush(imageArea->getBrush());
    painter.drawLine(QLine(start,end));
    painter.end();
    imageArea->update();
}
