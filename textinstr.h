#ifndef TEXTINSTR_H
#define TEXTINSTR_H
#include "commoninstr.h"
#include "textdialog.h"

class TextInstr : public CommonInstr
{
    Q_OBJECT
public:
    explicit TextInstr(QWidget *parent = 0);
    void mousePress(QMouseEvent*);
    void mouseMove(QMouseEvent *);
    void mouseRelease(QMouseEvent*);
    void setText(QString);
    void setFlags(bool);
signals:

public slots:

protected:
    void use();
private:
    bool isAllocated;
    QPoint click;
    TextDialog* textDialog;
    QString text;

};

#endif // TEXTINSTR_H
