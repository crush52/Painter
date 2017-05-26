#ifndef ENUMINSTRUMENTS_H
#define ENUMINSTRUMENTS_H
#include <QPoint>
const int numOfInstr = 4;
const QPoint initialPoint(50,100);
enum instrumentsEnum {
    RECT,
    ELLIPSE,
    ZOOM,
    FILL
};

#endif // ENUMINSTRUMENTS_H
