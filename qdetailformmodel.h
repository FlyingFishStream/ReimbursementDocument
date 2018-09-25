#ifndef QDETAILFORMMODEL_H
#define QDETAILFORMMODEL_H

#include <QWidget>
//#include <QLabel>
//#include <QLineEdit>
#include "qtlineedit.h"
#include "qtlabel.h"

#define DEF_FORM_MODEL_LE                0      //国内，标题，元
#define DEF_FORM_MODEL_LEE              1       //国内，标题，元/天/人
#define DEF_FORM_MODEL_LE_F                    2       //国外，不涉及到天数的报销项目
#define DEF_FORM_MODEL_LE_F_DAY         3       //国外，相关补助。尤其是涉及到天数的

class QDetailFormModel : public QWidget
{
    Q_OBJECT
public:
    explicit QDetailFormModel(int nModel = DEF_FORM_MODEL_LE,QWidget *parent = 0);
    void setWidgetTitle(QString strTitle, QString strLabelEdit1 = " ", QString strLabelEdit2 = " ");
    void getWidgetTitle(QString& strTitle, QString& strLabelEdit1, QString& strLabelEdit2);
    void getLineEdit(QString& strLineEdit1, QString& strLineEdit2);
    void setDays(const int nDays);
    void setPerCount(const int nPerCount);
    void setLimitDays(const int nLimitDays);
    void setDiscount(const double dDiscount);
    void setExchangeRate(const double dExchangeRate);
    void setUnit_F(const  QString strUnit);
    void getText(QString &strText,double &dYuan);
    QString getText1();
    void setText1(QString& str);
    QString getText2();
    void setText2(QString& str);
    void clearText();
private:
    int m_nModel;
    int m_nDays;
    int m_nPerCount;
    int m_nLimitDays;
    double m_dDiscount;
    double m_dExchangeRate;
    QString m_strUnit;
    QtLabel* m_pLabelTitle;
    QtLineEdit* m_pLineEdit1;
    QtLabel* m_pLabelEdit1;
    QtLineEdit* m_pLineEdit2;
    QtLabel* m_pLabelEdit2;
signals:
    void changed();
private slots:
    void changedSlot();
    void days2Little(const QString &strText);
    void doCopyLabelTitle();
public:
    bool isEmpt();
};

#endif // QDETAILFORMMODEL_H
