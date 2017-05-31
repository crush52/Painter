#include "imagearea.h"
#include <QPainter>
#include <QPaintEvent>
#include <QImage>
#include <QBrush>
#include <QFileDialog>
#include "rectangleinstr.h"
#include "ellipseinstr.h"
#include "zoominstr.h"
#include "fillinstr.h"
#include "lineinstr.h"
#include "pencilinstr.h"
#include "brushinstr.h"
#include "cutinstr.h"
#include <QtDebug>
#include <algorithm>
#include <cmath>


ImageArea::ImageArea(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(QRect(QPoint(0,0),QSize(600,400)));
    mainWindow = dynamic_cast<MainWindow*>(parent->parentWidget());
    image = new QImage(QSize(this->width()-10,this->height()-10),QImage::Format_ARGB32_Premultiplied);
//    image->setDevicePixelRatio(2.0);
    image->fill(Qt::white);
    headOfChanges = 0;
    pushChange();
    realSize = image->size();
    scaledFactor = 1;
    pen = new QPen(Qt::black,0,Qt::NoPen);
    brush = new QBrush(Qt::white, Qt::SolidPattern);
    imageColorFirst = new QImage(QSize(21,21),QImage::Format_ARGB32_Premultiplied);
    imageColorSecond = new QImage(QSize(21,21),QImage::Format_ARGB32_Premultiplied);

    imageCopy = new QImage(image->size(),QImage::Format_ARGB32_Premultiplied);
    clearImage = new QImage(image->size(),QImage::Format_ARGB32_Premultiplied);
    part_of_image = new QImage(image->size(),QImage::Format_ARGB32_Premultiplied);
    imageCopyForZoom = new QImage(image->size(),QImage::Format_ARGB32_Premultiplied);

    resizeFlag = false;
    changeFlag = false;
    changeAfterFlag = false;
    moveObjectFlag = false;
    isCut = false;
    dif = QPoint(0,0);
    fileName.clear();

    instruments.resize(numOfInstr);
    instruments[RECT] = new RectangleInstr(this);
    instruments[ELLIPSE] = new EllipseInstr(this);
    instruments[ZOOM] = new ZoomInstr(this);
    instruments[FILL] = new FillInstr(this);
    instruments[LINE] = new LineInstr(this);
    instruments[PENCIL] = new PencilInstr(this);
    instruments[BRUSH] = new BrushInstr(this);
    instruments[CUT] = new CutInstr(this);
}

void ImageArea::mousePressEvent(QMouseEvent *event)
{
    if(QRect(QPoint(image->width()*scaledFactor,image->height()*scaledFactor),QSize(7,7)).contains(event->pos()))
    {
        resizeFlag = true;
        changeAfterFlag = false;
        return;
    }
    //

    if(changeAfterFlag && choosenInstr == LINE &&
                QRect(end*scaledFactor+QPoint(1,1),QSize(7,7)).contains(event->pos()))
        {
            dif = QPoint(0,0);
            return;
        }
    else if(changeAfterFlag && QRect(start*scaledFactor,end*scaledFactor).contains(event->pos()))
    {
        if(choosenInstr != CUT)
        {
            moveObjectFlag = true;
            this->setCursor(Qt::OpenHandCursor);
            click = event->pos()/scaledFactor;
            return;
        }
    }
    else if(changeAfterFlag && choosenInstr!= LINE &&
            QRect(QPoint(std::max(start.x(),end.x()),std::max(start.y(),end.y()))*scaledFactor+QPoint(1,1),QSize(7,7)).contains(event->pos()))
    {
        start = QPoint(std::min(start.x(),end.x()),std::min(start.y(),end.y()));
//        if(start.x() < 0 || start.y() < 0) start = QPoint(0,0);
        instruments[choosenInstr]->setStartPoint(start);
        dif = QPoint(0,0);
        return;
    }
    else
    {
        changeAfterFlag = false;
        isCut = false;
        this->update();
        dif = QPoint(0,0);
    }

    isLeftButton = (event->button() == Qt::LeftButton);
    if(!isLeftButton)
    {
        brush->setColor(colorSecond);
        pen->setColor(colorFirst);
    }
//    *imageCopy = *image;

    if(clearImage->size().width()!=image->size().width() || clearImage->size().height()!=image->size().height())
    {
        delete clearImage;
        clearImage = new QImage(image->size(),QImage::Format_ARGB32_Premultiplied);
        clearImage->fill(Qt::transparent);
    }

    instruments[choosenInstr]->mousePress(event);
    start = instruments[choosenInstr]->getStartPoint();
}

void ImageArea::mouseMoveEvent(QMouseEvent *event)
{
    if(resizeFlag)
    {
        if(event->pos().x()>1 && event->pos().y()>1)// && fmod(event->pos().x(),scaledFactor) == 0 && fmod(event->pos().y(),scaledFactor) == 0)
        {
            end = event->pos();
            this->setGeometry(QRect(QPoint(0,0),QSize(std::max(end.x(),(int)(image->width()*scaledFactor))+11,std::max(end.y(),(int)(image->height()*scaledFactor))+11)));
            this->update();
            return;
        }
        else return;
    }
    /////////////////////////
    if(moveObjectFlag)
    {
        moveObject(event->pos()/scaledFactor);
        instruments[choosenInstr]->setStartPoint(start);
        instruments[choosenInstr]->setEndPoint(end);
        return;
    }
    /////////////////////////

    if(!isCut) *part_of_image = *clearImage;
    instruments[choosenInstr]->mouseMove(event);
    if(changeFlag)
    {
        QPainter painter;
        painter.begin(image);
        if(isCut)
            painter.drawImage(instruments[choosenInstr]->getStartPoint(),*part_of_image,part_of_image->rect());
        else
            painter.drawImage(image->rect(),*part_of_image,part_of_image->rect());
        painter.end();
        end = instruments[choosenInstr]->getEndPoint();
    }
    this->update();
}

void ImageArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(resizeFlag)
    {
        resize(event->pos().x()/scaledFactor,event->pos().y()/scaledFactor);
        resizeFlag = false;
        pushChange();
        this->update();
        return;
    }
    if(moveObjectFlag)
    {
        moveObjectFlag = false;
        this->setCursor(Qt::ArrowCursor);
        pushChange();
        return;
    }
    if(!isLeftButton)
    {
        brush->setColor(colorFirst);
        pen->setColor(colorSecond);
    }
    if(changeFlag)
        pushChange();
    instruments[choosenInstr]->mouseRelease(event);
    this->update();
}

void ImageArea::resize(int w, int h)
{
    w = (int)(w/scaledFactor)*scaledFactor;
    h = (int)(h/scaledFactor)*scaledFactor;
    QImage* imageCopy_ = new QImage(QSize(w,h),QImage::Format_ARGB32_Premultiplied);
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

void ImageArea::pushChange()
{
    if(headOfChanges<changes.size()-1)
    {
        changes[++headOfChanges] = *image;
        changes.resize(headOfChanges+1);
        return;
    }
    if(changes.size()>100)
        changes.pop_front();
    changes.push_back(*image);
    headOfChanges = changes.size()-1;
}


void ImageArea::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    if(scaledFactor != 1)
    {
        *imageCopyForZoom = image->scaled(image->size()*scaledFactor,Qt::KeepAspectRatio);
        painter.drawImage(0,0,*imageCopyForZoom,0,0);
    }
    else
        painter.drawImage(0,0,*image,0,0);

    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter.setPen(QPen(Qt::blue,2,Qt::SolidLine));
    painter.drawRect(image->width()*scaledFactor,image->height()*scaledFactor,7,7);
    if(changeAfterFlag)
    {
        if(choosenInstr != LINE)
            painter.drawRect(QRect(QPoint(std::max(start.x(),end.x()),std::max(start.y(),end.y()))*scaledFactor+QPoint(1,1),QSize(7,7)));
        else
            painter.drawRect(QRect(end*scaledFactor+QPoint(1,1),QSize(7,7)));

        painter.setBrush(Qt::NoBrush);
        painter.setPen(QPen(Qt::blue,1,Qt::SolidLine));
        painter.drawRect(QRect(start*scaledFactor,end*scaledFactor));
    }
    if(resizeFlag)
    {
        painter.setBrush(Qt::NoBrush);
        painter.setPen(QPen(Qt::blue,1,Qt::DashLine));
        painter.drawRect(QRect(QPoint(0,0),end));
    }
    if(isCut)
    {
        painter.setBrush(Qt::NoBrush);
        painter.setPen(QPen(Qt::blue,1,Qt::DashLine));
        painter.drawRect(QRect(instruments[choosenInstr]->getStartPoint(),instruments[choosenInstr]->getEndPoint()));
    }
    painter.end();
}

QImage* ImageArea::getPartOfImage(){    return part_of_image;}

QImage *ImageArea::getImage(){    return image;}

QImage *ImageArea::getImageCopy(){    return imageCopy;}

QImage *ImageArea::getImageCopyForZoom(){    return imageCopyForZoom;}

QPen ImageArea::getPen(){    return *pen;}

QBrush ImageArea::getBrush(){    return *brush;}

QSize ImageArea::getSize(){    return realSize;}

float ImageArea::getScaledFactor(){    return scaledFactor;}

void ImageArea::setScaledFactor(float scaledFactor){    this->scaledFactor = scaledFactor;}

void ImageArea::setChangeFlag(bool flag){    changeFlag = flag;}

void ImageArea::setChangeAfterFlag(bool flag){    changeAfterFlag = flag;}

void ImageArea::setCut(bool flag){    isCut = flag;}

bool ImageArea::isLeftButtonClicked(){    return isLeftButton;}

void ImageArea::setInstrument(int choice){    //instruments[CUT]->setFlags(false);
    choosenInstr = choice; changeAfterFlag = false;
                                              isCut = false; this->update();
                                         }

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

void ImageArea::saveFile()
{
    if(fileName.isEmpty()) saveAsFile();
    else image->save(fileName);
}

void ImageArea::openFile()
{
    fileName  = QFileDialog::getOpenFileName(this,"Open Image","","*.png *.jpg *.bmp");
    if(fileName.isEmpty()) return;
    image->load(fileName);
    changes.clear();
    headOfChanges = 0;
    pushChange();
    this->setGeometry(QRect(initialPoint,QSize(image->width()+10,image->height()+10)));
    this->update();
}

void ImageArea::saveAsFile()
{
    fileName = QFileDialog::getSaveFileName(0,tr("Save Image"),"Image.png","*.png ;; *.jpg ;; *.bmp");
//    fileName = QFileDialog::getSaveFileName(this,tr("Save image"));
    image->save(fileName);
}

void ImageArea::undo()
{
    changeAfterFlag = false;
    if(headOfChanges == 0)
        return;
    headOfChanges--;
    *image = changes[headOfChanges];
    this->update();
    return;
}

void ImageArea::redo()
{
    changeAfterFlag = false;
    if(headOfChanges == changes.size()-1)
        return;
    *image = changes[++headOfChanges];
    this->update();
    return;
}
