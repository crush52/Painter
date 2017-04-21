#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPoint>
#include "imagearea.h"
class ImageArea;

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
signals:

public slots:

protected:
//    void paintEvent(QPaintEvent *event);
    void paint();
private:
    QPoint start,end;
    ImageArea* image;
};

#endif // MYWIDGET_H
