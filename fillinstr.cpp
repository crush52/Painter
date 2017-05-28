#include "fillinstr.h"
#include <QPainter>

FillInstr::FillInstr(QWidget *parent) : CommonInstr(parent)
{
    imageArea = dynamic_cast<ImageArea*>(parent);
}

void FillInstr::mousePress(QMouseEvent *me)
{
    start = end = me->pos();
    use();
}

void FillInstr::mouseMove(QMouseEvent *me)
{
}

void FillInstr::mouseRelease(QMouseEvent *me)
{
}

void FillInstr::use()
{
    newColor = imageArea->getBrush().color().rgb();
    QImage& image = *(imageArea->getImage());
    oldColor = image.pixel(start);
    if(oldColor == newColor) return;
    recurse(start.x(),start.y(),image);
}

void FillInstr::recurse(int x, int y, QImage &image)
{
    int leftX = x-1, rightX = x;
    //Заивка текущей строки
    while(leftX>0 || rightX<image.width())
    {
        if(leftX>0 && image.pixel(leftX,y) == oldColor)
        {
            image.setPixel(leftX,y,newColor);
        }
        else if(rightX<image.width() && image.pixel(rightX,y) == oldColor)
        {
            image.setPixel(rightX,y,newColor);
        }
        leftX--;
        rightX++;
    }
    //Проверка вверхней строки
    leftX = x-1; rightX = x;
    while(leftX>0 || rightX<image.width())
    {
        if(y-1 > 0 && leftX>0 && image.pixel(leftX,y-1) == oldColor)
        {
            recurse(leftX,y-1,image);
        }
        else if(y-1 > 0 && rightX<image.width() && image.pixel(rightX,y-1) == oldColor)
        {
            recurse(rightX,y-1,image);
        }
        leftX--;
        rightX++;
    }
    //Проверка нижней строки
    leftX = x-1; rightX = x;
    while(leftX>0 || rightX<image.width())
    {
        if(y+1 < image.height() && leftX>0 && image.pixel(leftX,y+1) == oldColor)
        {
            recurse(leftX,y+1,image);
        }
        if(y+1 < image.height() && rightX<image.width() && image.pixel(rightX,y+1) == oldColor)
        {
            recurse(rightX,y+1,image);
        }
        leftX--;
        rightX++;
    }
}
