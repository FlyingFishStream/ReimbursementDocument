#include "qttextedit.h"
#include <QDebug>

QtTextEdit::QtTextEdit(QWidget *parent):
    QTextEdit(parent)
{

}

void QtTextEdit::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    emit mouseClicked();
}

void QtTextEdit::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    emit mouseMoveEvent();
}

void QtTextEdit::mouseMoved(QMouseEvent *event)
{
    Q_UNUSED(event)
    emit mouseMoved();
}

void QtTextEdit::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit mouseDoubleClickEvent();
}
