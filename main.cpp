#include "rectangleinstr.h"
#include "imagearea.h"
#include "mainwindow.h"
#include <QApplication>
#include <QPicture>
#include <QWidget>
#include <QPainter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow paintDevice;
    paintDevice.show();
    return a.exec();
}
