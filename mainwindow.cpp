#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagearea.h"
#include <QSignalMapper>
#include <iostream>
#include <QPainter>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(QRect(50,50,900,500));
    scrollArea = new QScrollArea(this);
    scrollArea->setGeometry(QRect(initialPoint,QPoint(size().width(),size().height())));
    imageArea = new ImageArea(scrollArea);
    imageColorFirst = new QImage(QSize(21,21),QImage::Format_ARGB32_Premultiplied);
    imageColorSecond = new QImage(QSize(21,21),QImage::Format_ARGB32_Premultiplied);
    scrollArea->setWidget(imageArea);
    scrollArea->setBackgroundRole(QPalette::Dark);


    //Установка инструментов по нажатию
    QSignalMapper* psigMapperInstrument = new QSignalMapper();
    QObject::connect(psigMapperInstrument,SIGNAL(mapped(int)),imageArea,SLOT(setInstrument(int)));
    psigMapperInstrument->setMapping(ui->rectangle,RECT);
    QObject::connect(ui->rectangle,SIGNAL(clicked()),psigMapperInstrument,SLOT(map()));
    psigMapperInstrument->setMapping(ui->ellipse,ELLIPSE);
    QObject::connect(ui->ellipse,SIGNAL(clicked()),psigMapperInstrument,SLOT(map()));
    psigMapperInstrument->setMapping(ui->zoom,ZOOM);
    QObject::connect(ui->zoom,SIGNAL(clicked()),psigMapperInstrument,SLOT(map()));
    psigMapperInstrument->setMapping(ui->fill,FILL);
    QObject::connect(ui->fill,SIGNAL(clicked()),psigMapperInstrument,SLOT(map()));
    psigMapperInstrument->setMapping(ui->lineInstr,LINE);
    QObject::connect(ui->lineInstr,SIGNAL(clicked()),psigMapperInstrument,SLOT(map()));
    psigMapperInstrument->setMapping(ui->pencil,PENCIL);
    QObject::connect(ui->pencil,SIGNAL(clicked()),psigMapperInstrument,SLOT(map()));
    psigMapperInstrument->setMapping(ui->brush,BRUSH);
    QObject::connect(ui->brush,SIGNAL(clicked()),psigMapperInstrument,SLOT(map()));
    psigMapperInstrument->setMapping(ui->cut,CUT);
    QObject::connect(ui->cut,SIGNAL(clicked()),psigMapperInstrument,SLOT(map()));

    //Установка толщины
    QObject::connect(ui->width,SIGNAL(valueChanged(int)),imageArea,SLOT(setWidth_(int)));

    //Установка цвета
    QSignalMapper* psigMapperColor = new QSignalMapper();
    QObject::connect(psigMapperColor,SIGNAL(mapped(QString)),imageArea,SLOT(setColor_(QString)));
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
    psigMapperColor->setMapping(ui->noColor,"transparent");
    QObject::connect(ui->noColor,SIGNAL(clicked()),psigMapperColor,SLOT(map()));

    //Установка типа линии
//    QSignalMapper* psigMapperStyle = new QSignalMapper();
    QObject::connect(ui->line,SIGNAL(currentIndexChanged(int)),imageArea,SLOT(setPenStyle_(int)));

    QSignalMapper* psigMapperNumOfColor = new QSignalMapper();
    QObject::connect(psigMapperNumOfColor,SIGNAL(mapped(int)),imageArea,SLOT(setNumOfColor(int)));
    psigMapperNumOfColor->setMapping(ui->colorFirst,1);
    QObject::connect(ui->colorFirst,SIGNAL(clicked()),psigMapperNumOfColor,SLOT(map()));
    psigMapperNumOfColor->setMapping(ui->colorSecond,2);
    QObject::connect(ui->colorSecond,SIGNAL(clicked()),psigMapperNumOfColor,SLOT(map()));

    //Menu
    //File
    ui->menuFile->addAction("Open...",imageArea,SLOT(openFile()),QKeySequence("CTRL+O"));
    ui->menuFile->addAction("Save",imageArea,SLOT(saveFile()),QKeySequence("CTRL+S"));
    ui->menuFile->addAction("Save as...",imageArea,SLOT(saveAsFile()),QKeySequence("F12"));

    //Edit
    ui->menuEdit->addAction("Undo",imageArea,SLOT(undo()),QKeySequence("CTRL+Z"));
    ui->menuEdit->addAction("Redo",imageArea,SLOT(redo()),QKeySequence("CTRL+Y"));


//    ui->actionSave = new QAction(this);
//    ui->actionSave->setShortcut(QKeySequence("CTRL+S"));
//    QObject::connect(ui->actionSave,SIGNAL(triggered()),imageArea,SLOT(save()));

    //Выбор начальных инструментов
    ui->rectangle->click();
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

void MainWindow::resizeEvent(QResizeEvent *re)
{
    scrollArea->setGeometry(QRect(initialPoint,QPoint(size().width()-initialPoint.x(),size().height()-initialPoint.y())));
}

void MainWindow::mousePressEvent(QMouseEvent *me)
{

}

void MainWindow::mouseMoveEvent(QMouseEvent *me)
{
}

void MainWindow::mouseReleaseEvent(QMouseEvent *me)
{

}


MainWindow::~MainWindow()
{
    delete ui;
}
