#include "textdialog.h"
#include "ui_textdialog.h"
#include "textinstr.h"
#include <QFontDialog>
#include <QDebug>

TextDialog::TextDialog(QWidget *parent) :
    QDialog(parent)
{
//    ui->setupUi(this);
//    text.clear();
    this->setGeometry(50,50,200,200);
    textEdit = new QTextEdit(this);
    textEdit->setGeometry(QRect(10,10,180,150));
    QPushButton* setFont = new QPushButton(this);
    setFont->setGeometry(QRect(10,170,70,22));
    setFont->setText("Set Font...");
    font = QFont("Helvetica [Cronyx]", 10);
    QObject::connect(setFont,SIGNAL(clicked(bool)),this,SLOT(setFont()));
    QObject::connect(textEdit,SIGNAL(textChanged()),this,SLOT(setText()));
//    QObject::connect(ui->textEdit,SIGNAL())
}

QFont TextDialog::getFont()
{
    return font;
}

TextDialog::~TextDialog()
{
}

void TextDialog::setFont()
{
    bool ok;
    font = QFontDialog::getFont(
                    &ok, QFont("Helvetica [Cronyx]", 10), this);
    if(ok)
        textEdit->setFont(font);
    else
    {
        textEdit->setFont(QFont("Helvetica [Cronyx]", 10));
        font = QFont("Helvetica [Cronyx]", 10);
    }
}

void TextDialog::setText()
{
    qDebug() << textEdit->toPlainText();
    dynamic_cast<TextInstr*>(this->parentWidget())->setText(textEdit->toPlainText());
}
