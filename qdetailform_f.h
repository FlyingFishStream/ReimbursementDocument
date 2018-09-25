#ifndef QDETAILFORM_F_H
#define QDETAILFORM_F_H

#include <QWidget>
#include "qdetailformmodel.h"

class QDetailForm_F :public QWidget
{
    Q_OBJECT
public:
    explicit QDetailForm_F(QWidget *parent = 0);
    double getText(QString &strText);
    void clearText();
    void getFormula(QString &strText);
    void setDays(const int nDays);
    void setLimitDays(const int nDays);
    void setDiscount(const double dDiscount);
    void setExchangeRate(const double dExchangeRate);
    void setUnit_F();
    void setPerCount(const int nPerCount);
    QString getKindle();
private:
    QVector<QDetailFormModel*> m_verpModel;
    QDetailFormModel* m_pKindle;
    QDetailFormModel* m_pDFMTicket;
    QDetailFormModel* m_pDFMFare;
    QDetailFormModel* m_pDFMFood;
    QDetailFormModel* m_pDFMTransportation;
    QDetailFormModel* m_pDFMUnAccommodation;
    QDetailFormModel* m_pDFMAccommodation;
    QDetailFormModel* m_pDFMIncidental;
    QDetailFormModel* m_pDFMTraining;

signals:
    void changed();
private slots:
    void changedSlot();
    void setWidgetTitles();
public:
//    bool isEmpt();
};

#endif // QDETAILFORM_F_H
