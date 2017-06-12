#include "textdialog.h"
#include "textinstr.h"
#include <QFontDialog>
#include <QPushButton>
#include <QDebug>
#include <QVBoxLayout>

TextDialog::TextDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setGeometry(50,50,200,200);
    textEdit = new QTextEdit(this);
    textEdit->setGeometry(QRect(10,10,180,150));
    QPushButton* setFont = new QPushButton(this);
    setFont->setGeometry(QRect(10,170,70,22));
    setFont->setText("Set Font...");
    QVBoxLayout* vbl = new QVBoxLayout(this);
    vbl->addWidget(textEdit,1);
    vbl->addWidget(setFont,2);
    font = QFont("Arial", 10);
    QObject::connect(setFont,SIGNAL(clicked(bool)),this,SLOT(setFont()));
    QObject::connect(textEdit,SIGNAL(textChanged()),this,SLOT(setText()));
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
                    &ok, QFont("Arial", 10), this);
    if(ok)
        textEdit->setFont(font);
}

void TextDialog::setText()
{
//    qDebug() << textEdit->toPlainText();
    dynamic_cast<TextInstr*>(this->parentWidget())->setText(textEdit->toPlainText());
}

void TextDialog::setInitialText(QString text)
{
    textEdit->setText(text);
}
