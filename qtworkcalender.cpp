#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "qtworkcalender.h"
#include <QDebug>

#define DEF_AGAIN       6

QtWorkCalender::QtWorkCalender()
{
    this->setWindowTitle("排班日历");
    this->resize(500,400);
    m_pCalendar = new QCalendarWidget(this);
    m_pLabel = new QLabel(this);

    QVBoxLayout* vlayout = new QVBoxLayout(this);

    vlayout->addWidget(m_pLabel);
    vlayout->addWidget(m_pCalendar);
    setLayout(vlayout);

    init();
    connect(m_pCalendar, SIGNAL(clicked(QDate)), this, SLOT(doText()));
}

void QtWorkCalender::initWork()
{
    m_vecWork.resize(DEF_AGAIN);
    m_vecWork[0] = "白班：三B 刘建红      夜班：二";
    m_vecWork[1] = "白班：一A 李福海      夜班：三";
    m_vecWork[2] = "白班：二B 刘锡军      夜班：一";
    m_vecWork[3] = "白班：三A 敖茂顺      夜班：二";
    m_vecWork[4] = "白班：一B 李炳楠      夜班：三";
    m_vecWork[5] = "白班：二A 陈远坤      夜班：一";
}

void QtWorkCalender::init()
{
    initWork();
}

void QtWorkCalender::showDay()
{
    QDate date;
    date = QDate::currentDate();
    showDay(date);
}

void QtWorkCalender::showDay(const QDate& date)
{
    m_pCalendar->setSelectedDate(date);
    doText();
}

void QtWorkCalender::doText()
{
    QString strDayBase = "20160829";
    QDate dateBase(2016, 8, 29);
    QDate date = m_pCalendar->selectedDate();
    int nDays = 0;

    nDays = dateBase.daysTo(date);
    nDays = nDays%DEF_AGAIN;

    nDays = (nDays+DEF_AGAIN)%DEF_AGAIN;
    m_pLabel->setText(m_vecWork[nDays]);
}
