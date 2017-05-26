#ifndef FILLINSTR_H
#define FILLINSTR_H
#include "commoninstr.h"

class FillInstr: public CommonInstr
{
    Q_OBJECT

public:
    explicit FillInstr(QWidget *parent = 0);
    void mousePress(QMouseEvent*);
    void mouseMove(QMouseEvent *);
    void mouseRelease(QMouseEvent*);
protected:
    void use();
private:
    void recurse(int x,int y,QImage& image);
    QColor newColor,oldColor;
};
#endif // FILLINSTR_H
