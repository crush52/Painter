#include "rectangleinstr.h"
#include <QPainter>

RectangleInstr::RectangleInstr(QWidget *parent) : CommonInstr(parent)
{
    imageArea = dynamic_cast<ImageArea*>(parent);
}

void RectangleInstr::mousePressEvent(QMouseEvent *event)
{
    start = event->pos();
}

void RectangleInstr::mouseMoveEvent(QMouseEvent *event)
{
    end = event->pos();
    paint();
}

void RectangleInstr::mouseReleaseEvent(QMouseEvent *event)
{
}

void RectangleInstr::paint()
{
    QPainter painter(imageArea->getImage());
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(imageArea->getPen());
    painter.setBrush(imageArea->getBrush());
    painter.drawRect(QRect(start,end));
    painter.end();
    imageArea->update();
}
