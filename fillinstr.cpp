#include "fillinstr.h"
#include <QPainter>

FillInstr::FillInstr(QWidget *parent) : CommonInstr(parent)
{
    imageArea = dynamic_cast<ImageArea*>(parent);
}

void FillInstr::mousePress(QMouseEvent *me)
{
    start = end = me->pos()/imageArea->getScaledFactor();
    use();
}

void FillInstr::mouseMove(QMouseEvent *me)
{
}

void FillInstr::mouseRelease(QMouseEvent *me)
{
    imageArea->setChangeFlag(false);
}

void FillInstr::use()
{
    imageArea->setChangeFlag(true);
    newColor = imageArea->getBrush().color().rgb();
    QImage& image = *(imageArea->getImage());
    oldColor = image.pixel(start);
    if(oldColor == newColor) return;
    recurse(start.x(),start.y(),image);
}

void FillInstr::recurse(int x, int y, QImage &image)
{
    int leftX = x-1, rightX = x;
    bool f1,f2;
    //Заивка текущей строки
    while((f1 = (leftX>=0 && image.pixel(leftX,y) == oldColor)) || (f2 = (rightX<image.width() && image.pixel(rightX,y) == oldColor)))
    {
        if(f1)
        {
            image.setPixel(leftX,y,newColor);
            leftX--;
        }
        else if(f2)
        {
            image.setPixel(rightX,y,newColor);
            rightX++;
        }
    }
    //Проверка вверхней строки
    for(int i = leftX+1; i<rightX;i++)
    {
        if(y-1 >= 0 && image.pixel(i,y-1) == oldColor)
        {
            recurse(i,y-1,image);
        }
    }
    //Проверка нижней строки
    for(int i = leftX+1; i<rightX;i++)
    {
        if(y+1 < image.height() && image.pixel(i,y+1) == oldColor)
        {
            recurse(i,y+1,image);
        }
    }
}
