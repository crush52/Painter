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

    virtual void mousePressEvent(QMouseEvent *) = 0;
    virtual void mouseMoveEvent(QMouseEvent *) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *) = 0;
signals:

public slots:
protected:
    QPoint start,end;
    ImageArea* imageArea;
};

#endif // COMMONINSTR_H
