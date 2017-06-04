#ifndef TEXTDIALOG_H
#define TEXTDIALOG_H

#include <QDialog>
#include <QTextEdit>

namespace Ui {
class TextDialog;
}

class TextDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TextDialog(QWidget *parent = 0);
    QFont getFont();
    ~TextDialog();

private:
//    Ui::TextDialog *ui;
    QTextEdit* textEdit;
    QFont font;
public slots:
    void setFont();
    void setText();
};

#endif // TEXTDIALOG_H
