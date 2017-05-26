#ifndef COMMONINSTR_H
#define COMMONINSTR_H

#include <QWidget>
#include <QMouseEvent>
#include "imagearea.h"
class ImageArea;

class CommonInstr : public QWidget
{
    Q_OBJECT
public:
    explicit CommonInstr(QWidget *parent = 0);
//    virtual void use() = 0;
    virtual void mousePress(QMouseEvent*) = 0;
    virtual void mouseMove(QMouseEvent *) = 0;
    virtual void mouseRelease(QMouseEvent*) = 0;
    void setStartPoint(QPoint);
    QPoint getStartPoint();
    QPoint getEndPoint();
signals:

public slots:
protected:
    QPoint start,end;
    ImageArea* imageArea;
};

#endif // COMMONINSTR_H
