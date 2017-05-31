#include "brushinstr.h"

BrushInstr::BrushInstr(QWidget *parent) : CommonInstr(parent)
{
    imageArea = dynamic_cast<ImageArea*>(parent);
}

void BrushInstr::mousePress(QMouseEvent *me)
{
    *(imageArea->getImageCopy()) = *(imageArea->getImage());

}

void BrushInstr::mouseMove(QMouseEvent *me)
{

}

void BrushInstr::mouseRelease(QMouseEvent *me)
{

}

void BrushInstr::use()
{

}
