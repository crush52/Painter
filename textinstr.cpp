#include "textinstr.h"
#include "textdialog.h"
#include <QPainter>
#include  <QTextEdit>
#include <iostream>

TextInstr::TextInstr(QWidget *parent) : CommonInstr(parent)
{
    imageArea = dynamic_cast<ImageArea*>(parent);
}

void TextInstr::mousePress(QMouseEvent *me)
{
    text.clear();
    start = end = me->pos()/imageArea->getScaledFactor();
//    *(imageArea->getImageCopy()) = *(imageArea->getImage());
}

void TextInstr::mouseMove(QMouseEvent *me)
{
    end = me->pos()/imageArea->getScaledFactor();
    use();
}

void TextInstr::mouseRelease(QMouseEvent *me)
{
    if(start == end) return;
    imageArea->setChangeFlag(false);
    imageArea->setChangeAfterFlag(true);
    createTextEdit();
}

void TextInstr::use()
{
    imageArea->setSelect(true);
    imageArea->update();
}

void TextInstr::createTextEdit()
{
    textDialog = new TextDialog(this);
    textDialog->show();
}

void TextInstr::setText(QString text)
{
//    imageArea->setChangeFlag(true);
//    *(imageArea->getImage()) = *(imageArea->getImageCopy());
//    QPainter painter(imageArea->getPartOfImage());
////    painter.setRenderHint(QPainter::Antialiasing, true);
//    painter.setPen(imageArea->getPen());
//    painter.setBrush(imageArea->getBrush());
//    painter.drawRect(QRect(start,end));
//    painter.end();
//    imageArea->update();
    this->text = text;
    imageArea->setChangeFlag(true);
//    *(imageArea->getImage()) = *(imageArea->getImageCopy());
    QPainter painter(imageArea->getImage());
    painter.setFont(textDialog->getFont());
    painter.drawText(QRect(start,end),text);
    painter.end();
    imageArea->update();
}

