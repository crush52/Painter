#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "enuminstruments.h"
#include <QScrollArea>
#include "imagearea.h"
class ImageArea;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setColorWidget(QImage*,QImage*);
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent*);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString colorFirst,colorSecond;
    QImage* imageColorFirst,*imageColorSecond;
    QScrollArea* scrollArea;
    ImageArea* imageArea;
};

#endif // MAINWINDOW_H
