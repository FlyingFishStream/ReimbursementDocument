#ifndef QTTEXTEDIT_H
#define QTTEXTEDIT_H
#include <QTextEdit>
#include <QWidget>

class QtTextEdit : public QTextEdit
{
    Q_OBJECT

public:
    QtTextEdit(QWidget *parent = NULL);

signals:
    void mouseClicked(void);
    void mouseMoveEvent(void);
    void mouseMoved(void);
    void mouseDoubleClickEvent(void);

protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseMoved(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // QTTEXTEDIT_H
