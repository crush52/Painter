#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "enuminstruments.h"

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
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString colorFirst,colorSecond;
    QImage* imageColorFirst,*imageColorSecond;
};

#endif // MAINWINDOW_H
