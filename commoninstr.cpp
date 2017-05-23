#include "commoninstr.h"

CommonInstr::CommonInstr(QWidget *parent) : QWidget(parent)
{

}

void CommonInstr::setStartPoint(QPoint start)
{
    this->start = start;
}

void CommonInstr::setEndPoint(QPoint end)
{
    this->end = end;
}
