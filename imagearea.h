#ifndef IMAGEAREA_H
#define IMAGEAREA_H

#include <QWidget>
#include <QImage>
#include <QVector>
#include <QPen>
#include <QBrush>
#include <QString>
#include "commoninstr.h"
class CommonInstr;
class MainWindow;
#include "enuminstruments.h"
#include "mainwindow.h"
#include <QScrollArea>
#include <QLabel>

class ImageArea : public QWidget
{
    Q_OBJECT
public:
    explicit ImageArea(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
    void resize(int w, int h, bool zoom);
    QImage* getPartOfImage();
    QImage* getImage();
    QImage* getImageCopy();

    QPen getPen();
    QBrush getBrush();
    QSize getSize();
    float getScaledFactor();
    void setScaledFactor(float);
    void setChangeFlag(bool);
    bool isLeftButtonClicked();
//    ~ImageArea();
signals:

public slots:
    void setInstrument(int);
    void setWidth_(int);
    void setColor_(QString);
    void setPenStyle_(int);
    void setNumOfColor(int);
private:
    QImage *image,*imageCopy,*part_of_image,*clearImage;
    QVector<CommonInstr*> instruments;
    QPen *pen;
    QBrush *brush;
    QImage* imageColorFirst,*imageColorSecond;
    QString colorFirst,colorSecond;
    MainWindow* mainWindow;
    QSize realSize;
    QPoint start,end;
    float scaledFactor;
    bool resizeFlag;
    int choosenInstr;
    int numOfColor;
    bool isLeftButton;
    bool changeFlag;


    bool flag;

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // IMAGEAREA_H
