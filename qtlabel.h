#ifndef QTLABEL_H
#define QTLABEL_H
#include <QLabel>
#include <QWidget>

class QtLabel : public QLabel
{\
    Q_OBJECT

public:
    QtLabel(QWidget *parent=0);

signals:
    void mouseClicked(void);
    void mouseMoved(void);
    void mouseDoubleClickEvent(void);

protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // QTLABEL_H
