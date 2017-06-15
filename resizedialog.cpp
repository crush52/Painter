#include "resizedialog.h"
#include "ui_resizedialog.h"

ResizeDialog::ResizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResizeDialog)
{
    ui->setupUi(this);
    imageArea = dynamic_cast<ImageArea*>(parent);
    QObject::connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(resize()));
}

ResizeDialog::~ResizeDialog()
{
    delete ui;
}

void ResizeDialog::setSize(int w, int h)
{
    ui->width->setText(QString::number(w));
    ui->height->setText(QString::number(h));
}

void ResizeDialog::resize()
{
    imageArea->setGeometry(QRect(QPoint(0,0),QSize(ui->width->text().toInt()+11,ui->height->text().toInt()+11)));
    imageArea->resize(ui->width->text().toInt(),ui->height->text().toInt());
    imageArea->pushChange();
}
