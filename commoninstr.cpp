#include "commoninstr.h"

CommonInstr::CommonInstr(QWidget *parent) : QWidget(parent)
{

}

void CommonInstr::setStartPoint(QPoint start)
{
    this->start = start;
}

QPoint CommonInstr::getStartPoint()
{
    return start;
}

QPoint CommonInstr::getEndPoint()
{
    return end;
}
