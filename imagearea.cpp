#include "imagearea.h"
#include <QPainter>
#include <QPaintEvent>
#include <QImage>
#include <QBrush>
#include <iostream>
#include "rectangleinstr.h"
#include "ellipseinstr.h"
#include "zoominstr.h"


ImageArea::ImageArea(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(QRect(initialPoint,QSize(600,400)));
//    std::cout << size().width() << ' ' << size().height() << std::endl;
    mainWindow = dynamic_cast<MainWindow*>(parent->parentWidget());

    image = new QImage(QSize(size().width()-10,size().height()-10),QImage::Format_ARGB32_Premultiplied);
//    image->setDevicePixelRatio(2.0);
    image->fill(Qt::white);
    realSize = image->size();
    scaledFactor = 1;
    pen = new QPen(Qt::black,0,Qt::NoPen);
    brush = new QBrush(Qt::white, Qt::SolidPattern);
    imageColorFirst = new QImage(QSize(21,21),QImage::Format_ARGB32_Premultiplied);
    imageColorSecond = new QImage(QSize(21,21),QImage::Format_ARGB32_Premultiplied);

    imageCopy = new QImage(image->size(),QImage::Format_ARGB32_Premultiplied);
    clearImage = new QImage(image->size(),QImage::Format_ARGB32_Premultiplied);
    part_of_image = new QImage(image->size(),QImage::Format_ARGB32_Premultiplied);

    start = end = QPoint(-1,-1);

    resizeFlag = false;
    changeFlag = false;

    instruments.resize(numOfInstr);
    instruments[RECT] = new RectangleInstr(this);
    instruments[ELLIPSE] = new EllipseInstr(this);
    instruments[ZOOM] = new ZoomInstr(this);
}

void ImageArea::mousePressEvent(QMouseEvent *event)
{
//    std::cout << event->pos().x() << ' ' << event->pos().y() << std::endl;
    if(event->pos().x()>image->width() && event->pos().x()<image->width()+7 &&
            event->pos().y()>image->height() && event->pos().y()<image->height()+7)
    {
        resizeFlag = true;
        return;
    }
    isLeftButton = (event->button() == Qt::LeftButton);
    if(!isLeftButton)
    {
        brush->setColor(colorSecond);
        pen->setColor(colorFirst);
    }
    *imageCopy = *image;
    start = end = event->pos();

    if(clearImage->size().width()!=image->size().width() || clearImage->size().height()!=image->size().height())
    {
        delete clearImage;
        clearImage = new QImage(image->size(),QImage::Format_ARGB32_Premultiplied);
    }

    instruments[choosenInstr]->mousePress(event);
//    instruments[choosenInstr]->setStartPoint(event->pos());
//    instruments[choosenInstr]->setEndPoint(event->pos());
//    instruments[choosenInstr]->use();
}

void ImageArea::mouseMoveEvent(QMouseEvent *event)
{
    std::cout << "MOVE " << event->pos().x() << ' ' << event->pos().y() << std::endl;
    if(resizeFlag)
    {
        if(event->pos().x()>1 && event->pos().y()>1)
        {
            resize(event->pos().x(),event->pos().y(), false);
            return;
        }
        else return;
    }

    end = event->pos();
    *part_of_image = *clearImage;
    *image = *imageCopy;
    instruments[choosenInstr]->mouseMove(event);
    if(changeFlag)
    {
        QPainter painter;
        painter.begin(image);
//        painter.drawImage(QRect(start,end),*part_of_image,QRect(start,end));
//        painter.drawImage(event->rect(),*part_of_image,event->rect());
        painter.drawImage(image->rect(),*part_of_image,part_of_image->rect());
        painter.end();
    }
//    instruments[choosenInstr]->setEndPoint(event->pos());
//    instruments[choosenInstr]->use();
}

void ImageArea::mouseReleaseEvent(QMouseEvent *event)
{
    std::cout << "RELEASE " << event->pos().x() << ' ' << event->pos().y() << std::endl;

    resizeFlag = false;
    if(!isLeftButton)
    {
        brush->setColor(colorFirst);
        pen->setColor(colorSecond);
    }
    instruments[choosenInstr]->mouseRelease(event);
}

void ImageArea::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Z && event->modifiers() & Qt::ShiftModifier)
    {
//        *image = *imageCopy;
        std::cout << "HI" << std::endl;
    }
}

void ImageArea::resize(int w, int h, bool zoom)
{
    this->setGeometry(QRect(initialPoint,QSize(w+10,h+10)));
    QImage* imageCopy_ = new QImage(QSize(w,h),QImage::Format_ARGB32_Premultiplied);
    if(!zoom)
        realSize = imageCopy_->size()/scaledFactor;
    imageCopy_->fill(Qt::white);
    QPainter painter;
    painter.begin(imageCopy_);
    painter.drawImage(0,0,*image);
    painter.end();
    delete image;
    image = imageCopy_;
}

QImage* ImageArea::getPartOfImage(){    return part_of_image;}

QImage *ImageArea::getImage()
{
    return image;
}

QImage *ImageArea::getImageCopy()
{
    return imageCopy;
}

QPen ImageArea::getPen(){    return *pen;}

QBrush ImageArea::getBrush(){    return *brush;}

QSize ImageArea::getSize()
{
    return realSize;
}

float ImageArea::getScaledFactor()
{
    return scaledFactor;
}

void ImageArea::setScaledFactor(float scaledFactor)
{
    this->scaledFactor = scaledFactor;
}

void ImageArea::setChangeFlag(bool flag)
{
    changeFlag = flag;
}

bool ImageArea::isLeftButtonClicked()
{
    return isLeftButton;
}


void ImageArea::setInstrument(int choice)
{
    choosenInstr = choice;
}

void ImageArea::setWidth_(int width)
{
    pen->setWidth(width);
}

void ImageArea::setColor_(QString color)
{
    if(numOfColor == 1)
    {
        brush->setColor(QColor(color));
        colorFirst = color;
    }
    else
    {
        pen->setColor(QColor(color));
        colorSecond = color;
    }
    QPainter painter;
    painter.begin(imageColorFirst);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black,4,Qt::SolidLine));
    painter.setBrush(QBrush(QColor(colorFirst), Qt::SolidPattern));
    painter.drawRect(QRect(QPoint(0,0),QPoint(21,21)));
    painter.end();
    painter.begin(imageColorSecond);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black,4,Qt::SolidLine));
    painter.setBrush(QBrush(QColor(colorSecond), Qt::SolidPattern));
    painter.drawRect(QRect(QPoint(0,0),QPoint(21,21)));
    painter.end();
    mainWindow->setColorWidget(imageColorFirst,imageColorSecond);
}

void ImageArea::setPenStyle_(int style)
{
    pen->setStyle(Qt::PenStyle(style));
}

void ImageArea::setNumOfColor(int number)
{
    numOfColor = number;
}

void ImageArea::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.drawImage(0,0,*image,0,0);

    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter.setPen(QPen(Qt::blue,2,Qt::SolidLine));
    painter.drawRect(image->width(),image->height(),7,7);

    painter.end();
}
