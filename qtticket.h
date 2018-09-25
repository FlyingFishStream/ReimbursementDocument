#ifndef QTTICKET_H
#define QTTICKET_H
#include "qtperinfodlg.h"
#include "qttextedit.h"
#include "qtlabel.h"
#include <QRadioButton>
#include <QGroupBox>
#include <QCheckBox>
#include <QPushButton>

class QtTicket : public QtPerInfoDlg
{
    Q_OBJECT


public:
    QtTicket(QWidget *parent = 0);
    ~QtTicket();

private:
    //layout
    QVBoxLayout *m_pVerticalLayout;

    QHBoxLayout *m_pHorizontaLayoutTicketKind;
    QHBoxLayout *m_pHorizontalLayoutBTravel;
    QHBoxLayout *m_pHorizontalLayoutBTEmail;

    QHBoxLayout *m_pHorizontalLayoutTime;
private:
    //label,lineEdit,pushButton...
    QRadioButton *m_pRBNo;
    QRadioButton *m_pRBGo;
    QRadioButton *m_pRBBack;
    QRadioButton *m_pRBGoBack;
    QCheckBox *m_pCheckBoxSeat;
    QGroupBox *m_pGroupBox;
    QLabel *m_pLabelBTravel;
    QLineEdit *m_pLineEditBTravel;
    QLabel *m_pLabelBTEmail;
    QLineEdit *m_pLineEditBTEmail;

    QLabel *m_pLabelTime;
    QLineEdit *m_pLineEditTime1;
    QLabel *m_pLabelTimeTo;
    QLineEdit *m_pLineEditTime2;

    QtLabel *m_pTLabel;
    QtTextEdit   *m_pTextEdit;
    QtLabel *m_pLabelFinish;
    QPushButton* m_pButtonFillPlanDocx;

private slots:
    void doText();
    void copyTitle();
    void copyText();
    void copyFinish();
    void fillPlanDocx();
private:
    int getTicketKind();
    void saveFillPlanDocxIni();
};

#endif // QTTICKET_H
