#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagearea.h"
#include <QSignalMapper>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ImageArea = new ImageArea(this);

    QSignalMapper* psigMapperInstrument = new QSignalMapper();
    QObject::connect(psigMapperInstrument,SIGNAL(mapped(int)),ui->ImageArea,SLOT(setInstrument(int)));
    psigMapperInstrument->setMapping(ui->Rectangle,RECT);
    QObject::connect(ui->Rectangle,SIGNAL(clicked()),psigMapperInstrument,SLOT(map()));
    psigMapperInstrument->setMapping(ui->Ellipse,ELLIPSE);
    QObject::connect(ui->Ellipse,SIGNAL(clicked()),psigMapperInstrument,SLOT(map()));

//    QObject::connect(ui->Width,SIGNAL(currentIndexChanged(int)),ui->ImageArea,SLOT(setWidth(int)));
    QObject::connect(ui->Width,SIGNAL(valueChanged(int)),ui->ImageArea,SLOT(setWidth_(int)));

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

}

MainWindow::~MainWindow()
{
    delete ui;
}

//((ImageArea*)ui->ImageArea)->rectInstr())
