#ifndef POLYGONALCHAININSTR_H
#define POLYGONALCHAININSTR_H
#include "commoninstr.h"

class PolygonalChainInstr : public CommonInstr
{
    Q_OBJECT
public:
    explicit PolygonalChainInstr(QWidget *parent = 0);
    void mousePress(QMouseEvent*);
    void mouseMove(QMouseEvent *);
    void mouseRelease(QMouseEvent*);
signals:

public slots:

protected:
    void use();
private:
    bool isFirstClick;
    bool stopDraw;
};

#endif // POLYGONALCHAININSTR_H
