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

    void resize(int w, int h);
    QImage* getPartOfImage();
    QImage* getImage();
    QImage* getImageCopy();
    QImage* getImageCopyForZoom();
    QPen getPen();
    QBrush getBrush();
    QSize getSize();
    float getScaledFactor();
    bool isAntialiasing();

    void setScaledFactor(float);
    void setChangeFlag(bool);
    void setChangeAfterFlag(bool);
    void setSelect(bool);

    bool isLeftButtonClicked();
//    ~ImageArea();
signals:

public slots:
    void setInstrument(int);
    void setWidth_(int);
    void setColor_(QString);
    void setPenStyle_(int);
    void setNumOfColor(int);
    void setAntialiasing(bool);
    void saveFile();
    void saveAsFile();
    void openFile();
    void undo();
    void redo();
    void copy();
    void paste();
    void cut();
    void deleteObj();
private:
    QImage *image,*imageCopy,*part_of_image,*clearImage,*imageCopyForZoom;
    QVector<CommonInstr*> instruments;
    QVector<QImage> changes;
    QPen *pen;
    QBrush *brush;
    QImage* imageColorFirst,*imageColorSecond;
    QString colorFirst,colorSecond;
    MainWindow* mainWindow;
    QSize realSize;
    QPoint start,end,click,dif;
    QString fileName;
    float scaledFactor;
    bool resizeFlag;
    int choosenInstr;
    int numOfColor;
    bool isLeftButton;
    bool changeFlag;
    bool changeAfterFlag;
    bool moveObjectFlag;
    bool isSelect;
    bool isPasted;
    bool antialiasing;
    int headOfChanges;

    void moveObject(QPoint);
    void pushChange();
protected:
    void paintEvent(QPaintEvent *event);

};

#endif // IMAGEAREA_H
