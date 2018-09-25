#include "qtlabel.h"

QtLabel::QtLabel(QWidget *parent):
    QLabel(parent)
{

}

void QtLabel::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    emit mouseClicked();
}

void QtLabel::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    emit mouseMoved();
}

void QtLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit mouseDoubleClickEvent();
}
