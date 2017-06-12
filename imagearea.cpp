#include "imagearea.h"
#include <QPainter>
#include <QPaintEvent>
#include <QImage>
#include <QBrush>
#include <QFileDialog>
#include <QColorDialog>
#include "rectangleinstr.h"
#include "ellipseinstr.h"
#include "zoominstr.h"
#include "fillinstr.h"
#include "lineinstr.h"
#include "pencilinstr.h"
#include "brushinstr.h"
#include "cutinstr.h"
#include "textinstr.h"
#include "pipetteinstr.h"
#include "polygonalchaininstr.h"
#include <QtDebug>
#include <QApplication>
#include <QClipboard>
#include <algorithm>
#include <cmath>


ImageArea::ImageArea(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(QRect(QPoint(0,0),QSize(600,400)));
    mainWindow = dynamic_cast<MainWindow*>(parent->parentWidget());
    image = new QImage(QSize(this->width()-10,this->height()-10),QImage::Format_ARGB32_Premultiplied);
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
    isSelect = false;
    antialiasing = false;
    isPasted = false;
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
    instruments[TEXT] = new TextInstr(this);
    instruments[PIPETTE] = new PipetteInstr(this);
    instruments[POLYGONALCHAIN] = new PolygonalChainInstr(this);
}

void ImageArea::mousePressEvent(QMouseEvent *event)
{
    //
    if(QRect(QPoint(image->width()*scaledFactor,image->height()*scaledFactor),QSize(7,7)).contains(event->pos()))
    {
        resizeFlag = true;
        changeAfterFlag = false;
        return;
    }
    //
    if(isPasted && QRect(QPoint(std::max(start.x(),end.x()),std::max(start.y(),end.y()))*scaledFactor+QPoint(1,1),QSize(7,7)).contains(event->pos()))
    {
        resizeFlag = true;
        return;
    }
    else if(isSelect && QRect(start*scaledFactor,end*scaledFactor).contains(event->pos()))
    {
        instruments[choosenInstr]->mousePress(event);
        start = instruments[choosenInstr]->getStartPoint();
        return;
    }
    else
    {
        isSelect = false;
        isPasted = false;
        dynamic_cast<CutInstr*>(instruments[CUT])->setFlags(false);
        this->update();
    }
    if(changeAfterFlag && choosenInstr == LINE &&
                QRect(end*scaledFactor+QPoint(1,1),QSize(7,7)).contains(event->pos()))
        {
            dif = QPoint(0,0);
            return;
        }
    else if(changeAfterFlag && QRect(start*scaledFactor,end*scaledFactor).contains(event->pos()))
    {
        moveObjectFlag = true;
        this->setCursor(Qt::OpenHandCursor);
        click = event->pos()/scaledFactor;
        return;
    }
    else if(changeAfterFlag && choosenInstr!= LINE &&
            QRect(QPoint(std::max(start.x(),end.x()),std::max(start.y(),end.y()))*scaledFactor+QPoint(1,1),QSize(7,7)).contains(event->pos()))
    {
        start = QPoint(std::min(start.x(),end.x()),std::min(start.y(),end.y()));
        instruments[choosenInstr]->setStartPoint(start);
        dif = QPoint(0,0);
        return;
    }
    else
    {
        dynamic_cast<TextInstr*>(instruments[TEXT])->setFlags(false);
        changeAfterFlag = false;
        dif = QPoint(0,0);
    }

    isLeftButton = (event->button() == Qt::LeftButton);
    if(!isLeftButton)
    {
        brush->setColor(colorSecond);
        pen->setColor(colorFirst);
    }

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
    if(resizeFlag && isPasted)
    {
        if(event->pos().x()>1 && event->pos().y()>1)
        {
            end = event->pos()/scaledFactor;
            instruments[choosenInstr]->setEndPoint(end);
            this->update();
        }
        return;
    }
    else if(resizeFlag)
    {
        if(event->pos().x()>1 && event->pos().y()>1)
        {
            end = event->pos();
            this->setGeometry(QRect(QPoint(0,0),QSize(std::max(end.x(),(int)(image->width()*scaledFactor))+11,std::max(end.y(),(int)(image->height()*scaledFactor))+11)));
            this->update();
            return;
        }
        else return;
    }
    else resizeFlag = false;

    /////////////////////////
    if(moveObjectFlag)
    {
        moveObject(event->pos()/scaledFactor);
        instruments[choosenInstr]->setStartPoint(start);
        instruments[choosenInstr]->setEndPoint(end);
        return;
    }
    /////////////////////////

    if(!isSelect)
        *part_of_image = *clearImage;
    instruments[choosenInstr]->mouseMove(event);
    end = instruments[choosenInstr]->getEndPoint();
    start = instruments[choosenInstr]->getStartPoint();
    if(changeFlag)
    {
        QPainter painter;
        painter.begin(image);
        if(isSelect)
            painter.drawImage(instruments[choosenInstr]->getStartPoint(),*part_of_image,part_of_image->rect());
        else
            painter.drawImage(image->rect(),*part_of_image,part_of_image->rect());
        painter.end();
    }
    this->update();
}

void ImageArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(resizeFlag && !isPasted)
    {
        resize(event->pos().x()/scaledFactor,event->pos().y()/scaledFactor);
        resizeFlag = false;
        pushChange();
        this->update();
        return;
    }
    else if(resizeFlag && isPasted)
    {
        *image = *imageCopy;
        QPainter painter(image);
        painter.drawImage(instruments[choosenInstr]->getStartPoint(),part_of_image->scaled(QSize((end-start).x(),(end-start).y()),Qt::IgnoreAspectRatio));
        painter.end();
        resizeFlag = false;
        this->update();
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
    if(changeAfterFlag || isPasted)
    {
        if(choosenInstr != LINE)
            painter.drawRect(QRect(QPoint(std::max(start.x(),end.x()),std::max(start.y(),end.y()))*scaledFactor+QPoint(1,1),QSize(7,7)));
        else
            painter.drawRect(QRect(end*scaledFactor+QPoint(1,1),QSize(7,7)));

        painter.setBrush(Qt::NoBrush);
        painter.setPen(QPen(Qt::blue,1,Qt::DashLine));
        painter.drawRect(QRect(start*scaledFactor,end*scaledFactor));
    }
    if(resizeFlag)
    {
        painter.setBrush(Qt::NoBrush);
        painter.setPen(QPen(Qt::blue,1,Qt::DashLine));
        if(!isPasted)
            painter.drawRect(QRect(QPoint(0,0),end));
    }
    if(isSelect)
    {
        painter.setBrush(Qt::NoBrush);
        painter.setPen(QPen(Qt::blue,1,Qt::DashLine));
        painter.drawRect(QRect(instruments[choosenInstr]->getStartPoint()*scaledFactor,
                               instruments[choosenInstr]->getEndPoint()*scaledFactor));
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

bool ImageArea::isAntialiasing(){    return antialiasing;}

void ImageArea::setScaledFactor(float scaledFactor){    this->scaledFactor = scaledFactor;}

void ImageArea::setChangeFlag(bool flag){    changeFlag = flag;}

void ImageArea::setChangeAfterFlag(bool flag){    changeAfterFlag = flag;}

void ImageArea::setSelect(bool flag){    isSelect = flag;}

bool ImageArea::isLeftButtonClicked(){    return isLeftButton;}

void ImageArea::setInstrument(int choice)
{
    dynamic_cast<TextInstr*>(instruments[TEXT])->setFlags(false);
    dynamic_cast<CutInstr*>(instruments[CUT])->setFlags(false);
    choosenInstr = choice;
    changeAfterFlag = false;
    isSelect = false;
    isPasted = false;
    this->update();
}

void ImageArea::setWidth_(int width){    pen->setWidth(width);}

void ImageArea::setColor_(QString color)
{
    if(color == "openDialog")
    {
        QColor tmpColor = QColorDialog::getColor();
        if(!tmpColor.isValid()) return;
        else color = tmpColor.name();
    }
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
    if(colorFirst == "transparent")
    {
        painter.setPen(QPen(Qt::black,4,Qt::SolidLine));
        painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
        painter.drawRect(QRect(QPoint(0,0),QPoint(21,21)));
        painter.drawText(QRect(QPoint(0,0),QPoint(21,21)),Qt::AlignCenter,"NC");
    }
    else
    {
        painter.setPen(QPen(Qt::black,4,Qt::SolidLine));
        painter.setBrush(QBrush(QColor(colorFirst), Qt::SolidPattern));
        painter.drawRect(QRect(QPoint(0,0),QPoint(21,21)));
    }
    painter.end();
    painter.begin(imageColorSecond);
    if(colorSecond == "transparent")
    {
        painter.setPen(QPen(Qt::black,4,Qt::SolidLine));
        painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
        painter.drawRect(QRect(QPoint(0,0),QPoint(21,21)));
        painter.drawText(QRect(QPoint(0,0),QPoint(21,21)),Qt::AlignCenter,"NC");
    }
    else
    {
        painter.setPen(QPen(Qt::black,4,Qt::SolidLine));
        painter.setBrush(QBrush(QColor(colorSecond), Qt::SolidPattern));
        painter.drawRect(QRect(QPoint(0,0),QPoint(21,21)));
    }
    mainWindow->setColorWidget(imageColorFirst,imageColorSecond);
}

void ImageArea::setPenStyle_(int style){    pen->setStyle(Qt::PenStyle(style));}

void ImageArea::setNumOfColor(int number){    numOfColor = number;}

void ImageArea::setAntialiasing(bool value){    antialiasing = value;}

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
    fileName = QFileDialog::getSaveFileName(0,tr("Save Image"),"Image.png","*.png *.jpg *.bmp");
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

void ImageArea::copy()
{
    if(isSelect)
    {
        QClipboard* cb = QApplication::clipboard();
        cb->setImage(*part_of_image);
    }
}

void ImageArea::paste()
{
    QClipboard* cb = QApplication::clipboard();
    QImage* pastedImage = new QImage(cb->image());
    if(!pastedImage->isNull())
    {
        dynamic_cast<TextInstr*>(instruments[TEXT])->setFlags(false);
        isSelect = false;
        this->update();
        setInstrument(CUT);
        isSelect = true;
        isPasted = true;
        *part_of_image = *pastedImage;
        start = QPoint(0,0);
        end = QPoint(part_of_image->width()-1,part_of_image->height()-1);
        instruments[choosenInstr]->setStartPoint(start);
        instruments[choosenInstr]->setEndPoint(end);
        dynamic_cast<CutInstr*>(instruments[CUT])->setFlags(true);
        dynamic_cast<CutInstr*>(instruments[CUT])->setFirstClick(false);
        *imageCopy = *image;
        QPainter painter;
        painter.begin(image);
        painter.drawImage(start,*part_of_image,part_of_image->rect());
        painter.end();
        pushChange();
    }
}

void ImageArea::cut()
{
    copy();
    deleteObj();
}

void ImageArea::deleteObj()
{
    if(isSelect)
    {
        dynamic_cast<CutInstr*>(instruments[CUT])->setFlags(false);
        isSelect = false;
        QPainter painter;
        painter.begin(image);
        painter.fillRect(QRect(start,end),Qt::white);
        painter.end();
        *part_of_image = *clearImage;
        this->update();
        pushChange();
    }
}
