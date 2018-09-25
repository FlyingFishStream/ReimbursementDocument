#ifndef QTREIMDOMESTIC_H
#define QTREIMDOMESTIC_H
#include "qtperinfodlg.h"
#include "qtlabel.h"
#include "qttextedit.h"
#include "qdatecompute.h"
#include "qdetailform.h"
#include <QGroupBox>
#include <QRadioButton>
#include "qtlineedit.h"

class QtReimDomestic : public QtPerInfoDlg
{
    Q_OBJECT
public:
   explicit QtReimDomestic(QWidget* parent = 0);
private:
    // layout
    QVBoxLayout* m_pVerticalLayout;
    QHBoxLayout* m_pHorizontalLayoutEvent;
    QHBoxLayout* m_pHorizontalLayoutDocTitle;
    QHBoxLayout* m_pHorizontalLayoutTicket;
private:
    // layel textEdit lineEdit...
    QLabel* m_pLabelEvent;
    QtLineEdit* m_pLineEditEvent;
    QLabel* m_pLabelDocTitle;
    QtLineEdit* m_pLineEditDocTitle;
    QDateCompute* m_pDateCompute;
    QDetailForm* m_pDForm;
    QGroupBox* m_pGroupBoxTicket;
    QVector<QRadioButton*> m_verpRadioButtonTicket;

    QtLabel* m_pLabelTitle;
    QtLabel* m_pLabelShowEvent;
    QtTextEdit* m_pTextEditText;
private:
    void addTicketString(QString &strText);
    void getEventFromDocTitle(QString &strText);
private slots:
    void setShowEvent();
    void doText();
    void copyTitle();
    void copyShowEvent();
    void copyText();
};

#endif // QTREIMDOMESTIC_H
