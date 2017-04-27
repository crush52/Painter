#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagearea.h"
#include <QSignalMapper>
#include <iostream>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ImageArea = new ImageArea(this);
    imageColorFirst = new QImage(QSize(21,21),QImage::Format_ARGB32_Premultiplied);
    imageColorSecond = new QImage(QSize(21,21),QImage::Format_ARGB32_Premultiplied);

    //Установка инструментов по нажатию
    QSignalMapper* psigMapperInstrument = new QSignalMapper();
    QObject::connect(psigMapperInstrument,SIGNAL(mapped(int)),ui->ImageArea,SLOT(setInstrument(int)));
    psigMapperInstrument->setMapping(ui->Rectangle,RECT);
    QObject::connect(ui->Rectangle,SIGNAL(clicked()),psigMapperInstrument,SLOT(map()));
    psigMapperInstrument->setMapping(ui->Ellipse,ELLIPSE);
    QObject::connect(ui->Ellipse,SIGNAL(clicked()),psigMapperInstrument,SLOT(map()));

    //Установка толщины
    QObject::connect(ui->Width,SIGNAL(valueChanged(int)),ui->ImageArea,SLOT(setWidth_(int)));

    //Установка цвета
    QSignalMapper* psigMapperColor = new QSignalMapper();
    QObject::connect(psigMapperColor,SIGNAL(mapped(QString)),ui->ImageArea,SLOT(setColor_(QString)));
    psigMapperColor->setMapping(ui->red,"red");
    QObject::connect(ui->red,SIGNAL(clicked()),psigMapperColor,SLOT(map()));
    psigMapperColor->setMapping(ui->white,"white");
    QObject::connect(ui->white,SIGNAL(clicked()),psigMapperColor,SLOT(map()));
    psigMapperColor->setMapping(ui->blue,"blue");
    QObject::connect(ui->blue,SIGNAL(clicked()),psigMapperColor,SLOT(map()));
    psigMapperColor->setMapping(ui->yellow,"yellow");
    QObject::connect(ui->yellow,SIGNAL(clicked()),psigMapperColor,SLOT(map()));
    psigMapperColor->setMapping(ui->green,"green");
    QObject::connect(ui->green,SIGNAL(clicked()),psigMapperColor,SLOT(map()));
    psigMapperColor->setMapping(ui->black,"black");
    QObject::connect(ui->black,SIGNAL(clicked()),psigMapperColor,SLOT(map()));

    //Установка типа линии
//    QSignalMapper* psigMapperStyle = new QSignalMapper();
    QObject::connect(ui->Line,SIGNAL(currentIndexChanged(int)),ui->ImageArea,SLOT(setPenStyle_(int)));

    QSignalMapper* psigMapperNumOfColor = new QSignalMapper();
    QObject::connect(psigMapperNumOfColor,SIGNAL(mapped(int)),ui->ImageArea,SLOT(setNumOfColor(int)));
    psigMapperNumOfColor->setMapping(ui->colorFirst,1);
    QObject::connect(ui->colorFirst,SIGNAL(clicked()),psigMapperNumOfColor,SLOT(map()));
    psigMapperNumOfColor->setMapping(ui->colorSecond,2);
    QObject::connect(ui->colorSecond,SIGNAL(clicked()),psigMapperNumOfColor,SLOT(map()));


    //Выбор начальных инструментов
    ui->Rectangle->click();
    ui->colorSecond->click();
    ui->black->click();
    ui->colorFirst->click();
    ui->white->click();
}

void MainWindow::setColorWidget(QImage* imageColorFirst,QImage* imageColorSecond)
{
    this->imageColorFirst = imageColorFirst;
    this->imageColorSecond = imageColorSecond;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.drawImage(ui->colorFirstView->pos().x(),ui->colorFirstView->pos().y()+13,*imageColorFirst);
    painter.drawImage(ui->colorSecondView->pos().x(),ui->colorSecondView->pos().y()+13,*imageColorSecond);
    painter.end();
    this->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//((ImageArea*)ui->ImageArea)->rectInstr())
