#include "textinstr.h"
#include "textdialog.h"
#include <QPainter>
#include  <QTextEdit>
#include <iostream>

TextInstr::TextInstr(QWidget *parent) : CommonInstr(parent)
{
    imageArea = dynamic_cast<ImageArea*>(parent);
    textDialog = new TextDialog(this);
}

void TextInstr::mousePress(QMouseEvent *me)
{
    if(isAllocated)
        return;
    else
    {
        *(imageArea->getImageCopy()) = *(imageArea->getImage());
        start = end = me->pos()/imageArea->getScaledFactor();
    }
}

void TextInstr::mouseMove(QMouseEvent *me)
{
    if(!isAllocated)
        use();
    end = me->pos()/imageArea->getScaledFactor();
}

void TextInstr::mouseRelease(QMouseEvent *me)
{
    if(start == end) return;
    if(!isAllocated)
    {
        text.clear();
        textDialog->setInitialText(text);
        textDialog->show();
        isAllocated = true;
    }
    else
    {
        textDialog->setInitialText(text);
        setText(text);
        imageArea->update();
    }
    imageArea->setChangeFlag(false);
    imageArea->setChangeAfterFlag(true);
    imageArea->setSelect(false);
    imageArea->setCursor(Qt::ArrowCursor);
}

void TextInstr::use()
{
    imageArea->setSelect(true);
    imageArea->setChangeFlag(true);
    imageArea->update();
}

void TextInstr::setText(QString text)
{
    this->text = text;
    *(imageArea->getImage()) = *(imageArea->getImageCopy());
    imageArea->getPartOfImage()->fill(Qt::transparent);
    QPainter painter(imageArea->getPartOfImage());
    painter.setRenderHint(QPainter::Antialiasing,imageArea->isAntialiasing());
    painter.setFont(textDialog->getFont());
    painter.setPen(imageArea->getPen().color());
    painter.drawText(QRect(start,end),text);
    painter.end();
    painter.begin(imageArea->getImage());
    painter.drawImage(0,0,*(imageArea->getPartOfImage()));
    painter.end();
    imageArea->update();
}

void TextInstr::setFlags(bool flag)
{
    isAllocated = flag;
}

