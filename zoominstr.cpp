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

void ZoomInstr::mouseMove(QMouseEvent *){}

void ZoomInstr::mouseRelease(QMouseEvent *){}

void ZoomInstr::use()
{
    if(imageArea->isLeftButtonClicked() && scaledFactor <= 6)
        scaledFactor+=0.5;
    else if(!(imageArea->isLeftButtonClicked()) && scaledFactor > 0.5 )
        scaledFactor-=0.5;
    else return;
    scaledSize=imageArea->getImage()->size()*scaledFactor;
    *(imageArea->getImageCopyForZoom()) = imageArea->getImage()->scaled(scaledSize,Qt::KeepAspectRatio);
    imageArea->setScaledFactor(scaledFactor);
    imageArea->setGeometry(QRect(initialPoint,QSize(scaledSize.width()+10,scaledSize.height()+10)));
    imageArea->update();
}
