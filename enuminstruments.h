#ifndef ENUMINSTRUMENTS_H
#define ENUMINSTRUMENTS_H
#include <QPoint>
const int numOfInstr = 10;
const QPoint initialPoint(30,130);
enum instrumentsEnum {
    RECT,
    ELLIPSE,
    LINE,
    PENCIL,
    ZOOM,
    FILL,
    CUT,
    TEXT,
    PIPETTE,
    POLYGONALCHAIN
};

#endif // ENUMINSTRUMENTS_H
