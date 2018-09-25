#ifndef QTEXCHANGERATE_H
#define QTEXCHANGERATE_H

#include "data.h"
#include <QWidget>
#include <QVector>
#include <QDate>
#include "qdetailformmodel.h"

class QtExchangeRate : public QWidget
{
    Q_OBJECT
public:
    explicit QtExchangeRate(QWidget* parent = 0);
private:
    QVector<QDetailFormModel*> m_verpModel;
    QDetailFormModel* m_pOutDate;
    QDetailFormModel* m_pInDate;
    QDetailFormModel* m_pOutExchangeRate;
    QDetailFormModel* m_pInExchangeRate;
    QDetailFormModel* m_pDateLimit;
    QDetailFormModel* m_pDiscount;
public:
    void getInDate(QDate& date);
    QDate getInDate();
    void getOutDate(QDate& date);
    QDate getOutDate();
    int computeDays();
    void getInExchangeRate(double& dExchangeRate);
    void getOutExchangeRate(double& dExchangeRate);
    void getDateLimit(double& dDay);
    void setDateLimit(double dDay);
    void getDiscount(double& dDiscount);
    void setDiscount(double dDiscount);
    void getText(QString& strText);
private slots:
    void changedSlot();
signals:
    void changed();
};

#endif // QTEXCHANGERATE_H
