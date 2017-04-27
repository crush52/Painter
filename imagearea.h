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
#include "enuminstruments.h"

class ImageArea : public QWidget
{
    Q_OBJECT
public:
    explicit ImageArea(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
    QImage* getImage();
    QPen getPen();
    QBrush getBrush();
signals:

public slots:
    void setInstrument(int);
    void setWidth_(int);
    void setColor_(QString);
    void setPenStyle_(int);
    void setNumOfColor(int);
private:
    QImage *image,*imageCopy;
    QVector<CommonInstr*> instruments;
    QPen *pen;
    QBrush *brush;
    QImage* imageColorFirst,*imageColorSecond;
    QString colorFirst,colorSecond;
    int choosenInstr;
    int numOfColor;

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // IMAGEAREA_H
