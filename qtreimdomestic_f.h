#ifndef QTREIMDOMESTIC_F_H
#define QTREIMDOMESTIC_F_H
#include "qtperinfodlg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QLabel>
#include "qtlineedit.h"
#include "qdatecompute.h"
#include "qdetailform.h"
#include "qtexchangerate.h"
#include "qdetailform_f.h"
#include "qtlabel.h"
#include "qttextedit.h"

class QtReimDomestic_F : public QtPerInfoDlg
{
    Q_OBJECT
public:
    explicit QtReimDomestic_F(QWidget* parent = 0);
    void init();

private:
    //layout
    QVBoxLayout* m_pVerticalLayout;
    QHBoxLayout* m_pHorizontalLayoutEvent;
    QHBoxLayout* m_pHorizontalLayoutDateCompute;
    QHBoxLayout* m_pHorizontalLayoutForm;
    QVBoxLayout* m_pVerticalLayoutText;
private:
    QLabel* m_pLabelEvent;
    QtLineEdit* m_pLineEditEvent;
    QDateCompute* m_pDateCompute;
    QDetailForm* m_pDForm;
    QtExchangeRate* m_pExchangeRate;
    QDetailForm_F* m_pDForm_F;
    QtLabel* m_pDocTitle;
    QtLabel* m_pDocEvent;
    QtTextEdit* m_pTextEdit;

private slots:
    void doText();
    void copyTitle();
    void copyShowEvent();
    void copyText();
};

#endif // QTREIMDOMESTIC_F_H
