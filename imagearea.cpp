#include "imagearea.h"
#include <QPainter>
#include <QPaintEvent>
#include <QImage>
#include <QBrush>
#include <iostream>
#include "rectangleinstr.h"
#include "ellipseinstr.h"

ImageArea::ImageArea(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(50,100,parent->size().width()-5,parent->size().height()-5);
    image = new QImage(size(),QImage::Format_ARGB32_Premultiplied);
    pen = new QPen(Qt::black,0,Qt::DashLine);
    brush = new QBrush(QBrush(Qt::white, Qt::SolidPattern));
//    QPainter painter;
//    painter.begin(image);
//    painter.setBackground(QBrush(Qt::GlobalColor::white));
//    painter.end();
    imageCopy = new QImage(size(),QImage::Format_ARGB32_Premultiplied);
    instruments.resize(numOfInstr);
    instruments[RECT] = new RectangleInstr(this);
    instruments[ELLIPSE] = new EllipseInstr(this);
}

void ImageArea::mousePressEvent(QMouseEvent *event)
{
    *imageCopy = *image;
    instruments[choosenInstr]->mousePressEvent(event);
}

void ImageArea::mouseMoveEvent(QMouseEvent *event)
{
    *image = *imageCopy;
    instruments[choosenInstr]->mouseMoveEvent(event);
}

void ImageArea::mouseReleaseEvent(QMouseEvent *event)
{
    instruments[choosenInstr]->mouseReleaseEvent(event);
}

void ImageArea::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Z && event->modifiers() & Qt::ShiftModifier)
    {
        *image = *imageCopy;
        std::cout << "HI" << std::endl;
    }
}

QImage* ImageArea::getImage()
{
    return image;
}

QPen ImageArea::getPen()
{
    return *pen;
}

QBrush ImageArea::getBrush()
{
    return *brush;
}

void ImageArea::setInstrument(int choice)
{
    choosenInstr = choice;
    //    std::cout << choice << std::endl;
}

void ImageArea::setWidth_(int width)
{
    pen->setWidth(width);
}

void ImageArea::setColor_(QString color)
{
    brush->setColor(QColor(color));
//    std::cout << color << std::endl;
}

void ImageArea::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
//    painter.drawRect(0, 0,
//                          image->rect().right() - 1,
//                          image->rect().bottom() - 1);
    painter.drawImage(event->rect(),*image,event->rect());
//    painter.drawRect(QRect(image->rect().right(),
//                                image->rect().bottom(), 6, 6));
    painter.end();
}
