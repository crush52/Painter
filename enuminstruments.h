#ifndef ENUMINSTRUMENTS_H
#define ENUMINSTRUMENTS_H
#include <QPoint>
const int numOfInstr = 11;
const QPoint initialPoint(50,120);
enum instrumentsEnum {
    RECT,
    ELLIPSE,
    LINE,
    PENCIL,
    BRUSH,
    ZOOM,
    FILL,
    CUT,
    TEXT,
    PIPETTE,
    POLYGONALCHAIN
};

#endif // ENUMINSTRUMENTS_H
