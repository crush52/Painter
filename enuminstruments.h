#ifndef ENUMINSTRUMENTS_H
#define ENUMINSTRUMENTS_H
#include <QPoint>
const int numOfInstr = 8;
const QPoint initialPoint(50,100);
enum instrumentsEnum {
    RECT,
    ELLIPSE,
    LINE,
    PENCIL,
    BRUSH,
    ZOOM,
    FILL,
    CUT
};

#endif // ENUMINSTRUMENTS_H
