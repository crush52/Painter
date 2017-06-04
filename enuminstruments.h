#ifndef ENUMINSTRUMENTS_H
#define ENUMINSTRUMENTS_H
#include <QPoint>
const int numOfInstr = 9;
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
    TEXT
};

//enum textEnum{
//    BOLD,
//    ITALIC,
//    UNDERLINED
//};

#endif // ENUMINSTRUMENTS_H
