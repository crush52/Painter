#include "mywidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <iostream>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    image = (ImageArea*)parent;
//    std::cout << image << std::endl;
}

void MyWidget::mousePressEvent(QMouseEvent *event)
{
    start = event->pos();
    end = start;
    paint();
//    std::cout << start.x() << ' ' << start.y() << ' ' << end.x() << ' ' << end.y() << std::endl;
}

void MyWidget::mouseMoveEvent(QMouseEvent *event)
{
    end = event->pos();
    paint();
//    std::cout << start.x() << ' ' << start.y() << ' ' << end.x() << ' ' << end.y() << std::endl;
//    paintEvent();
//    paint();
}

void MyWidget::mouseReleaseEvent(QMouseEvent *event)
{
    end = event->pos();
    paint();
//    paintEvent();
//    paint();
}

void MyWidget::paint()
{

    QPainter painter(image->getImage());
    painter.setRenderHint(QPainter::Antialiasing, true);

    //painter.setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));

    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));

    painter.drawRect(QRect(start,end));
    painter.end();
    image->update();
}

//void MyWidget::paintEvent(QPaintEvent *event)
//{
//    QPainter painter;
//    painter.begin(this);
//    painter.setRenderHint(QPainter::Antialiasing, true);

//    painter.setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));

//    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));

//    painter.drawRect(QRect(start,end));
//    this->update();

//}
// start.x(),start.y(), end.x(),end.y()
