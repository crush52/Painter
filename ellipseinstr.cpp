#include "ellipseinstr.h"
#include <QPainter>

EllipseInstr::EllipseInstr(QWidget *parent) : CommonInstr(parent)
{
    imageArea = (ImageArea*)parent;
}

void EllipseInstr::mousePressEvent(QMouseEvent *event)
{
    start = event->pos();
}

void EllipseInstr::mouseMoveEvent(QMouseEvent *event)
{
    end = event->pos();
    paint();
}

void EllipseInstr::mouseReleaseEvent(QMouseEvent *event)
{

}

void EllipseInstr::paint()
{
    QPainter painter(imageArea->getImage());
    painter.setRenderHint(QPainter::Antialiasing, true);

    //painter.setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));
    painter.setPen(imageArea->getPen());
//    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    painter.setBrush(imageArea->getBrush());
    painter.drawEllipse(QRect(start,end));
    painter.end();
    imageArea->update();
}
