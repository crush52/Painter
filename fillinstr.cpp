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
    newColor = imageArea->getBrush().color();
    QImage& image = *(imageArea->getImage());
    oldColor = image.pixelColor(start);
    int x = start.x(), y = start.y();

    recurse(start.x(),start.y(),image);
}

void FillInstr::recurse(int x, int y, QImage &image)
{
    int x_left = x;
    while(true)
    {
        if(image.pixelColor(x_left,y) != oldColor)
            break;
        if(x_left > 1) x_left--;
        else break;
    }
    int y_up = y;
    while(true)
    {
        if(image.pixelColor(x_left,y) != oldColor)
            break;
        if(x_left > 1) x_left--;
        else break;
    }
}
