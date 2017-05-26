#include "imagearea.h"
#include <QPainter>
#include <QPaintEvent>
#include <QImage>
#include <QBrush>
#include <iostream>
#include "rectangleinstr.h"
#include "ellipseinstr.h"
#include "zoominstr.h"
#include "fillinstr.h"
#include <QtDebug>
#include <algorithm>


ImageArea::ImageArea(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(QRect(initialPoint,QSize(600,400)));
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

    resizeFlag = false;
    changeFlag = false;
    changeAfterFlag = false;
    moveObjectFlag = false;
    dif = QPoint(0,0);

    instruments.resize(numOfInstr);
    instruments[RECT] = new RectangleInstr(this);
    instruments[ELLIPSE] = new EllipseInstr(this);
    instruments[ZOOM] = new ZoomInstr(this);
    instruments[FILL] = new FillInstr(this);
}

void ImageArea::mousePressEvent(QMouseEvent *event)
{
    //
    if(QRect(QPoint(image->width(),image->height()),QSize(7,7)).contains(event->pos()))
    {
        resizeFlag = true;
        changeAfterFlag = false;
        return;
    }
    //

    if(changeAfterFlag && QRect(start,end).contains(event->pos()))
    {
        moveObjectFlag = true;
        click = event->pos();
        return;
    }
    else if(changeAfterFlag &&
            QRect(QPoint(std::max(start.x(),end.x()),std::max(start.y(),end.y()))+QPoint(1,1),QSize(7,7)).contains(event->pos()))
    {
        instruments[choosenInstr]->setStartPoint(QPoint(std::min(start.x(),end.x()),std::min(start.y(),end.y())));
        start = QPoint(std::min(start.x(),end.x()),std::min(start.y(),end.y()));
        return;
    }
    else
    {
        changeAfterFlag = false;
        this->update();
        dif = QPoint(0,0);
    }

    isLeftButton = (event->button() == Qt::LeftButton);
    if(!isLeftButton)
    {
        brush->setColor(colorSecond);
        pen->setColor(colorFirst);
    }
    *imageCopy = *image;

    if(clearImage->size().width()!=image->size().width() || clearImage->size().height()!=image->size().height())
    {
        delete clearImage;
        clearImage = new QImage(image->size(),QImage::Format_ARGB32_Premultiplied);
    }

    instruments[choosenInstr]->mousePress(event);
    start = instruments[choosenInstr]->getStartPoint();
}

void ImageArea::mouseMoveEvent(QMouseEvent *event)
{
    if(resizeFlag)
    {
        if(event->pos().x()>1 && event->pos().y()>1)
        {
            resize(event->pos().x(),event->pos().y(), false);
            return;
        }
        else return;
    }
    /////////////////////////
    if(moveObjectFlag)
    {
        moveObject(event->pos());
        return;
    }
    /////////////////////////

    *part_of_image = *clearImage;
    instruments[choosenInstr]->mouseMove(event);
    if(changeFlag)
    {
        QPainter painter;
        painter.begin(image);
        painter.drawImage(image->rect(),*part_of_image,part_of_image->rect());
        painter.end();
        end = instruments[choosenInstr]->getEndPoint();
    }
}

void ImageArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(moveObjectFlag)
    {
        moveObjectFlag = false;
        return;
    }
    resizeFlag = false;
    if(!isLeftButton)
    {
        brush->setColor(colorFirst);
        pen->setColor(colorSecond);
    }
    instruments[choosenInstr]->mouseRelease(event);
    this->update();
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

void ImageArea::moveObject(QPoint mousePoint)
{
    *image = *imageCopy;
    QPainter painter;
    start = start + mousePoint - click;
    end = end + mousePoint - click;
    dif += mousePoint - click;
    painter.begin(image);
    painter.drawImage(dif,*part_of_image,part_of_image->rect());
    painter.end();
    click = mousePoint;
    this->update();
    return;
}


void ImageArea::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.drawImage(0,0,*image,0,0);

    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter.setPen(QPen(Qt::blue,2,Qt::SolidLine));
    painter.drawRect(image->width(),image->height(),7,7);
    if(changeAfterFlag)
    {
        painter.drawRect(QRect(QPoint(std::max(start.x(),end.x()),std::max(start.y(),end.y()))+QPoint(1,1),QSize(7,7)));
        painter.setBrush(Qt::NoBrush);
        painter.setPen(QPen(Qt::blue,1,Qt::SolidLine));
        painter.drawRect(QRect(start,end));
    }
    painter.end();
}

QImage* ImageArea::getPartOfImage(){    return part_of_image;}

QImage *ImageArea::getImage(){    return image;}

QImage *ImageArea::getImageCopy(){    return imageCopy;}

QPen ImageArea::getPen(){    return *pen;}

QBrush ImageArea::getBrush(){    return *brush;}

QSize ImageArea::getSize(){    return realSize;}

float ImageArea::getScaledFactor(){    return scaledFactor;}

void ImageArea::setScaledFactor(float scaledFactor){    this->scaledFactor = scaledFactor;}

void ImageArea::setChangeFlag(bool flag){    changeFlag = flag;}

void ImageArea::setChangeAfterFlag(bool flag){    changeAfterFlag = flag;}

bool ImageArea::isLeftButtonClicked(){    return isLeftButton;}

void ImageArea::setInstrument(int choice){    choosenInstr = choice;}

void ImageArea::setWidth_(int width){    pen->setWidth(width);}

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

void ImageArea::setPenStyle_(int style){    pen->setStyle(Qt::PenStyle(style));}

void ImageArea::setNumOfColor(int number){    numOfColor = number;}
