#ifndef QTWORKCALENDER_H
#define QTWORKCALENDER_H

#include <QCalendarWidget>
#include <QLabel>
#include <QDialog>

class QtWorkCalender: public QDialog
{
    Q_OBJECT

public:
    QtWorkCalender();
    void init();
    void showDay();
    void showDay(const QDate &date);
protected:
    void initWork();
private:
    QCalendarWidget* m_pCalendar;
    QLabel* m_pLabel;
    QVector<QString> m_vecWork;
private slots:
    void doText();
};

#endif // QTWORKCALENDER_H
