#ifndef RESIZEDIALOG_H
#define RESIZEDIALOG_H

#include <QDialog>
#include "imagearea.h"

namespace Ui {
class ResizeDialog;
}

class ResizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResizeDialog(QWidget *parent = 0);
    ~ResizeDialog();
    void setSize(int w,int h);

private:
    Ui::ResizeDialog *ui;
    ImageArea* imageArea;
public slots:
    void resize();
};

#endif // RESIZEDIALOG_H
