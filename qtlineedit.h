#ifndef QTLINEEDIT_H
#define QTLINEEDIT_H

#include <QLineEdit>

class QtLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    QtLineEdit(QWidget* parent = 0);

signals:
    void mouseClicked(void);
    void mousePress(void);
    void mouseMoved(void);
    void mouseDoubleClickEvent(void);

protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // QTLINEEDIT_H
