#include "zoominstr.h"

ZoomInstr::ZoomInstr(QWidget *parent)
    : CommonInstr(parent)
{
    imageArea = dynamic_cast<ImageArea*>(parent);
    scaledFactor = 1;
    scaledSize = imageArea->getSize();
}

void ZoomInstr::mousePress(QMouseEvent *)
{
    use();
}

void ZoomInstr::mouseMove(QMouseEvent *)
{

}

void ZoomInstr::mouseRelease(QMouseEvent *)
{

}


void ZoomInstr::use()
{
    if(imageArea->isLeftButtonClicked() && scaledFactor <= 8)
        scaledFactor+=0.5;
    else if(!(imageArea->isLeftButtonClicked()) && scaledFactor > 0.5 )
        scaledFactor-=0.5;
    else return;
    scaledSize=imageArea->getSize()*scaledFactor;
    *(imageArea->getImage()) = imageArea->getImage()->scaled(scaledSize,Qt::KeepAspectRatio);
    imageArea->setScaledFactor(scaledFactor);
    imageArea->resize(scaledSize.width(),scaledSize.height(),true);
    imageArea->update();
}
