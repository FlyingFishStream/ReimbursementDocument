#ifndef QDATECOMPUTE_H
#define QDATECOMPUTE_H

#include <QWidget>
#include <QLabel>
//#include <QLineEdit>
#include "qtlineedit.h"
#include <QHBoxLayout>
#include "data.h"

class QDateCompute : public QWidget
{
    Q_OBJECT
public:
    explicit QDateCompute(QWidget *parent = 0);
    int getDateCompute();
    void setWidgetTitle(const QString &strTitle);
    QDate getDate1();
    QDate getDate2();
signals:
    void changed();

public slots:
    void doCompute();
    void doCopyTime1();
    void doCopyTime2();

private:
    QHBoxLayout* m_pHBoxLayout;
    QLayout* m_pLayout;
    QLabel* m_pLabel;
    QtLineEdit* m_pLineEditTime1;
    QtLineEdit* m_pLineEditTime2;
    QLabel* m_pLabelCompute;
};

#endif // QDATECOMPUTE_H
