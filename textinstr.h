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
signals:

public slots:

protected:
    void use();
private:
    void createTextEdit();
    TextDialog* textDialog;
    QString text;

};

#endif // TEXTINSTR_H
