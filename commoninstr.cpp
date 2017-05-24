#include "commoninstr.h"

CommonInstr::CommonInstr(QWidget *parent) : QWidget(parent)
{

}

QPoint CommonInstr::getStartPoint()
{
    return start;
}

QPoint CommonInstr::getEndPoint()
{
    return end;
}
