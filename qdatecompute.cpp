#include "qdatecompute.h"
#include "qttools.h"
#include <QDate>
#include <QDebug>

QDateCompute::QDateCompute(QWidget *parent) : QWidget(parent)
{
    m_pHBoxLayout = new QHBoxLayout(this);
//    m_pLayout = new QLayout(m_pHBoxLayout);
    m_pLabel = new QLabel();
    m_pLabel->setText("出差天数计算器：");
    m_pLineEditTime1 = new QtLineEdit();
    m_pLineEditTime2 = new QtLineEdit();
    m_pLabelCompute = new QLabel();
    m_pLabelCompute->setText("0");

    m_pHBoxLayout->addWidget(m_pLabel);
    m_pHBoxLayout->addWidget(m_pLineEditTime1);
    m_pHBoxLayout->addWidget(m_pLineEditTime2);
    m_pHBoxLayout->addWidget(m_pLabelCompute);

    connect(m_pLineEditTime1, SIGNAL(textChanged(QString)), this, SLOT(doCompute()));
    connect(m_pLineEditTime2, SIGNAL(textChanged(QString)), this, SLOT(doCompute()));
    connect(m_pLineEditTime1, SIGNAL(mousePress()), this, SLOT(doCopyTime1()));
    connect(m_pLineEditTime2, SIGNAL(mousePress()), this, SLOT(doCopyTime2()));
}

int QDateCompute::getDateCompute()
{
    QString str = m_pLabelCompute->text();
    return str.toInt();
}

void QDateCompute::setWidgetTitle(const QString &strTitle)
{
    m_pLabel->setText(strTitle);
}

QDate QDateCompute::getDate1()
{
    QDate date1,date2;
    QString strDate1 = m_pLineEditTime1->text();
    QString strDate2 = m_pLineEditTime2->text();

    if(strDate1.size()+1 != sizeof(DATEFORMAT) ||
            strDate2.size() +1 != sizeof(DATEFORMAT))
    {
        return date1;
    }
    date1 = QDate::fromString(strDate1, DATEFORMAT);
    date2 = QDate::fromString(strDate2, DATEFORMAT);

    if(date1 > date2)
    {
        return date2;
    }
    return date1;
}

QDate QDateCompute::getDate2()
{
    QDate date1,date2;
    QString strDate1 = m_pLineEditTime1->text();
    QString strDate2 = m_pLineEditTime2->text();

    if(strDate1.size()+1 != sizeof(DATEFORMAT) ||
            strDate2.size() +1 != sizeof(DATEFORMAT))
    {
        return date2;
    }
    date1 = QDate::fromString(strDate1, DATEFORMAT);
    date2 = QDate::fromString(strDate2, DATEFORMAT);

    if(date1 > date2)
    {
        return date1;
    }
    return date2;
}

void QDateCompute::doCompute()
{
    QDate date1;
    QDate date2;
    int nCount = 0;
    QString strDate1 = m_pLineEditTime1->text();
    QString strDate2 = m_pLineEditTime2->text();
    m_pLabelCompute->setText("0");

    if(strDate1.size()+1 != sizeof(DATEFORMAT) ||
            strDate2.size() +1 != sizeof(DATEFORMAT))
    {
        return ;
    }
    date1 = QDate::fromString(strDate1, DATEFORMAT);
    date2 = QDate::fromString(strDate2, DATEFORMAT);

    nCount = date1.daysTo(date2);

    nCount = qAbs(nCount) + 1;
    m_pLabelCompute->setText(QString::number(nCount));

    emit changed();
}

void QDateCompute::doCopyTime1()
{
    QString str = m_pLineEditTime1->text();
    copyStringToPaste(str);
}

void QDateCompute::doCopyTime2()
{
    QString str = m_pLineEditTime2->text();
    copyStringToPaste(str);
}
