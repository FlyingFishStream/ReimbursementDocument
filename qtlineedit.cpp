#include "qtlineedit.h"

QtLineEdit::QtLineEdit(QWidget *parent):
    QLineEdit(parent)
{

}

void QtLineEdit::mouseReleaseEvent(QMouseEvent *event)
{
     Q_UNUSED(event)
    emit mouseClicked();
}

void QtLineEdit::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    emit mousePress();
}

void QtLineEdit::mouseMoveEvent(QMouseEvent *event)
{
     Q_UNUSED(event)
    emit mouseMoved();
}

void QtLineEdit::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit mouseDoubleClickEvent();
}
