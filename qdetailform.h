#ifndef QDETAILFORM_H
#define QDETAILFORM_H

#include <QWidget>
#include "qdetailformmodel.h"
#include "data.h"

class QDetailForm : public QWidget
{
    Q_OBJECT
public:
    explicit QDetailForm(QWidget *parent = 0);
    double getText(QString &strText);
    void clearText();
    void getFormula(QString &strText);
    void setDays(const int nDays);
    void setPerCount(const int nPerCount);
private:
    QVector<QDetailFormModel*> m_verpModel;
    QDetailFormModel* m_pDFMTicket;
    QDetailFormModel* m_pDFMFare;
    QDetailFormModel* m_pDFGrants;
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
public:
    bool isEmpt();
};

#endif // QDETAILFORM_H
