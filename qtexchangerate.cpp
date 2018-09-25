#include "qtexchangerate.h"
#include <QVBoxLayout>

QtExchangeRate::QtExchangeRate(QWidget *parent)
    :QWidget(parent)
{
    m_verpModel.clear();
    m_pOutDate = new QDetailFormModel();
    m_pInDate = new QDetailFormModel();
    m_pOutExchangeRate = new QDetailFormModel();
    m_pInExchangeRate = new QDetailFormModel();
    m_pDateLimit = new QDetailFormModel();
    m_pDiscount = new QDetailFormModel();

    m_verpModel.append(m_pOutDate);
    m_verpModel.append(m_pInDate);
    m_verpModel.append(m_pOutExchangeRate);
    m_verpModel.append(m_pInExchangeRate);
    m_verpModel.append(m_pDateLimit);
    m_verpModel.append(m_pDiscount);

    m_pOutDate->setWidgetTitle("出境日期：");
    m_pInDate->setWidgetTitle("入境日期：");
    m_pOutExchangeRate->setWidgetTitle("出境汇率：");
    m_pInExchangeRate->setWidgetTitle("入境汇率：");
    m_pDateLimit->setWidgetTitle("设置补贴打折限制天数：");
    m_pDiscount->setWidgetTitle("补贴打折：");

    QVBoxLayout* layout = new QVBoxLayout(this);
    for(int i  = 0; i < m_verpModel.count(); i++)
    {
        connect(m_verpModel[i], SIGNAL(changed()), this, SLOT(changedSlot()));
        layout->addWidget(m_verpModel[i]);
    }
    setLayout(layout);
}

void QtExchangeRate::getInDate(QDate& date)
{
    date = QDate::fromString(m_pInDate->getText1(), DATEFORMAT);
}

QDate QtExchangeRate::getInDate()
{
    return QDate::fromString(m_pInDate->getText1(), DATEFORMAT);
}

void QtExchangeRate::getOutDate(QDate& date)
{
    date = QDate::fromString(m_pOutDate->getText1(), DATEFORMAT);
}

QDate QtExchangeRate::getOutDate()
{
    return QDate::fromString(m_pOutDate->getText1(), DATEFORMAT);
}

int QtExchangeRate::computeDays()
{
    QDate inDate = getInDate();
    int count = inDate.daysTo(getOutDate());
    return  qAbs(count)+1;
}

void QtExchangeRate::getInExchangeRate(double& dExchangeRate)
{
    dExchangeRate = m_pInExchangeRate->getText1().toDouble();
}

void QtExchangeRate::getOutExchangeRate(double& dExchangeRate)
{
    dExchangeRate = m_pOutExchangeRate->getText1().toDouble();
}

void QtExchangeRate::getDateLimit(double& dDay)
{
    dDay = m_pDateLimit->getText1().toDouble();
}

void QtExchangeRate::setDateLimit(double dDay)
{
    QString str = QString::number(dDay);
    del0(str);
    m_pDateLimit->setText1(str);
}

void QtExchangeRate::getDiscount(double& dDiscount)
{
    dDiscount = m_pDiscount->getText1().toDouble();
}

void QtExchangeRate::setDiscount(double dDiscount)
{
    QString str = QString::number(dDiscount);
    del0(str);
    m_pDiscount->setText1(str);
}

void QtExchangeRate::getText(QString &strText)
{
    /*2016年10月30日汇率为：6.7858
2017年1月23日汇率为：6.8572
中间汇率为：（6.7858+6.8572）/2=6.8215*/
    strText.clear();
    QDate date1 = getOutDate();
    QDate date2 = getInDate();
    double dRate1;
    double dRate2;
    double dRateM;
    getOutExchangeRate(dRate1);
    getInExchangeRate(dRate2);
    dRateM = (dRate1 + dRate2)/2;
    QString strRate1 = QString::number(dRate1);
    QString strRate2 = QString ::number(dRate2);
    QString strRateM = QString::number(dRateM);
    del0(strRate1);
    del0(strRate2);
    del0(strRateM);
    strText = QString("%1汇率为:%2\n").arg(date1.toString(DATECHNFORMAT), strRate1);
    strText += QString("%1汇率为:%2\n").arg(date2.toString(DATECHNFORMAT), strRate2);
    strText += QString("中间汇率为：(%1+%2)/2=%3").arg(strRate1, strRate2, strRateM);
}

void QtExchangeRate::changedSlot()
{
    emit changed();
}
