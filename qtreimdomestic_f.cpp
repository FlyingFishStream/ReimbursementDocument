#include "qttools.h"
#include "qtreimdomestic_f.h"

QtReimDomestic_F::QtReimDomestic_F(QWidget *parent)
    :QtPerInfoDlg(parent)
{
    setWindowTitle("国际报销");
    this->resize(800,900);

    m_pVerticalLayout = new QVBoxLayout();
    m_pHorizontalLayoutEvent = new QHBoxLayout();
    m_pHorizontalLayoutDateCompute = new QHBoxLayout();
    m_pHorizontalLayoutForm = new QHBoxLayout();
    m_pVerticalLayoutText = new QVBoxLayout();

    m_pLabelEvent = new QLabel("报销事件：");
    m_pLineEditEvent = new QtLineEdit();
    m_pDateCompute = new QDateCompute();
    m_pDateCompute->setWidgetTitle(QString("总出差时间:"));
    m_pDForm = new QDetailForm();
    m_pExchangeRate = new QtExchangeRate();
    m_pDForm_F = new QDetailForm_F();
    m_pDocTitle = new QtLabel();
    m_pDocEvent = new QtLabel();
    m_pTextEdit = new QtTextEdit();

    m_pHorizontalLayoutEvent->addWidget(m_pLabelEvent);
    m_pHorizontalLayoutEvent->addWidget(m_pLineEditEvent);
    m_pHorizontalLayoutDateCompute->addWidget(m_pDateCompute);
    m_pHorizontalLayoutForm->addWidget(m_pDForm);
    m_pHorizontalLayoutForm->addWidget(m_pExchangeRate);
    m_pHorizontalLayoutForm->addWidget(m_pDForm_F);
    m_pVerticalLayoutText->addWidget(m_pDocTitle);
    m_pVerticalLayoutText->addWidget(m_pDocEvent);
    m_pVerticalLayoutText->addWidget(m_pTextEdit);

    m_pVerticalLayout->addLayout(m_pHorizontalLayoutEvent);
    m_pVerticalLayout->addLayout(m_pHorizontalLayoutDateCompute);
    m_pVerticalLayout->addLayout(m_pHorizontalLayoutForm);
    m_pVerticalLayout->addLayout(m_pVerticalLayoutText);

    ui.verticalLayout->addLayout(m_pVerticalLayout);
    setLayout(ui.verticalLayout);

    connect(ui.lineEdit, SIGNAL(textChanged(QString)), this, SLOT(doText()));
    connect(m_pLineEditEvent, SIGNAL(textChanged(QString)), this, SLOT(doText()));
    connect(m_pDateCompute, SIGNAL(changed()), this, SLOT(doText()));
    connect(m_pDForm, SIGNAL(changed()), this, SLOT(doText()));
    connect(m_pExchangeRate, SIGNAL(changed()), this, SLOT(doText()));
    connect(m_pDForm_F, SIGNAL(changed()), this, SLOT(doText()));

    connect(m_pDocTitle, SIGNAL(mouseClicked()), this, SLOT(copyTitle()));
    connect(m_pDocEvent, SIGNAL(mouseClicked()), this, SLOT(copyShowEvent()));
    connect(m_pTextEdit, SIGNAL(mouseClicked()), this, SLOT(copyText()));
}

void QtReimDomestic_F::init()
{
    m_pExchangeRate->setDateLimit((double)m_ini.nLimitDays);
   m_pExchangeRate->setDiscount(m_ini.dDiscount);
}

void QtReimDomestic_F::doText()
{
    if(m_pLineEditEvent->text().isEmpty())
    {
        return ;
    }
    else
    {
        m_pDocEvent->setText( m_pLineEditEvent->text() );
    }

    {
        double dTmp, dInTmp, dOutTmp;

        m_pExchangeRate->getDateLimit(dTmp);
        m_pDForm_F->setLimitDays((int)dTmp);

        m_pExchangeRate->getDiscount(dTmp);
        m_pDForm_F->setDiscount(dTmp);

        m_pExchangeRate->getInExchangeRate(dInTmp);
        m_pExchangeRate->getOutExchangeRate(dOutTmp);
        m_pDForm_F->setExchangeRate( (dInTmp+dOutTmp)/2 );

        m_pDForm_F->setUnit_F();
    }

     QVector<Perinfo> vPerInfo;
     getPerInfoInfact(vPerInfo);

     if(vPerInfo.count() <= DEF_ZERO)
     {
         return ;
     }
    QString strTitle;
    QString strText;
    QString strTmp;
    strTitle = "关于"+m_ini.strPlace;
    strText = "各位领导：\n    现申请报销"+m_ini.strWorkGroup;
    for(int i = 0; i < vPerInfo.count(); i++)
    {
        if( i == 0)
        {
            strTmp.clear();
            strTmp +=vPerInfo[i].name;
            strTmp += "（";
            strTmp += vPerInfo[i].id;
            strTmp += "）";
            strTitle += strTmp;
            strText += strTmp;
            strTmp.clear();
        }
        else
        {
            strText += "、";
            strText += vPerInfo[i].name;
            if( i == vPerInfo.count() -1 &&
                    vPerInfo.count() > 1)
            {
                strTmp.clear();
                strTmp = QString::number(vPerInfo.count());
                strTmp+="人";
                strText += strTmp;
                strTitle += "等" +strTmp;
                strTmp.clear();
            }
        }
    }
    m_pDForm->setPerCount(vPerInfo.count());
    m_pDForm_F->setPerCount(vPerInfo.count());
    strTitle += m_pLineEditEvent->text().trimmed()+"的差旅费报销申请";
    m_pDocTitle->setText(strTitle);
    strText +=m_pLineEditEvent->text().trimmed()+"的差旅费。\n";

    QDate date1 = m_pDateCompute->getDate1();
    QDate date2 = m_pExchangeRate->getOutDate();
    QDate date3 = m_pExchangeRate->getInDate();
    QDate date4 = m_pDateCompute->getDate2();
    int nAllDay = m_pDateCompute->getDateCompute();
    int nFirstDays = date1.daysTo(date2);
    int nSecondDays = date2.daysTo(date3)+1;
    int nThirdDays = date3.daysTo(date4);
    m_pDForm->setDays(nFirstDays+nThirdDays);
    m_pDForm_F->setDays(nSecondDays);

    strText += ui.lineEdit->text()+QString("共计出差%1天。").arg(QString::number(nAllDay));

    if(nFirstDays+nThirdDays == 0)
    {//只有国际出差
        strText += QString("其中");
        OUTSIDE:
        if(nSecondDays == 1)
        {
            strText += QString("国际出差共%1天(%2)。").arg( QString::number(nSecondDays), date3.toString(DATESHOWFORMAT) );
        }
        else
        {
            strText += QString("国际出差共%1天(%2-%3)。").arg( QString::number(nSecondDays), date2.toString(DATESHOWFORMAT), date3.toString(DATESHOWFORMAT));
        }
    }
    else
    {
        switch(nFirstDays)
        {
        case 0:
            strTmp = "";
            break;
        case 1:
            strTmp = date1.toString(DATESHOWFORMAT);
            break;
        default:
            strTmp = QString("%1-%2").arg(date1.toString(DATESHOWFORMAT), date2.addDays(-1).toString(DATESHOWFORMAT));
            break;
        }

        switch(nThirdDays)
        {
        case 0:
            // do nothing;
            break;
        case 1:
            if(nFirstDays != 0)
            {
                strTmp += "，";
            }
            strTmp += QString("%1").arg( date4.toString(DATESHOWFORMAT));
            break;
        default:
            if(nFirstDays != 0)
            {
                strTmp  += "，";
            }
            strTmp += QString("%1-%2").arg( date3.addDays(1).toString(DATESHOWFORMAT), date4.toString(DATESHOWFORMAT));
            break;
        }
        strText += QString("其中国内出差共%1天（%2），").arg( QString::number(nFirstDays+nThirdDays), strTmp);
        goto OUTSIDE;
    }

    double dInYuan, dOutYuan;
    strText += "\n" + m_ini.strFinanceFile;
    strText += "\n";
    dInYuan = m_pDForm->getText(strTmp);
    if(! strTmp.isEmpty())
    {
        strText += "\n人民币部分：\n";
        strText += strTmp + "。\n共计：";
        m_pDForm->getFormula(strTmp);
        strText += strTmp +"。\n";
    }

    dOutYuan = m_pDForm_F->getText(strTmp);
    if(! strTmp.isEmpty())
    {
//        strText += "\n国际部分：\n";
        strText +="\n"+m_pDForm_F->getKindle()+"部分：\n";
        m_pExchangeRate->getText(strTmp);
        strText += strTmp + "\n";
        m_pDForm_F->getText(strTmp);
        strText += strTmp + "。\n共计：";
        m_pDForm_F->getFormula(strTmp);
        strText += strTmp + "。\n";
    }

    if( dInYuan == 0)
    {
        strTmp = QString::number(dOutYuan);
        del0(strTmp);
        strText += QString("\n合计报销金额为：%1元。\n    妥否，请领导批示。").arg(strTmp);
    }
    else
    {
        QString strIn = QString::number(dInYuan);
        QString strOut = QString::number(dOutYuan);
        del0(strIn);
        del0(strOut);
        strTmp = QString::number(dInYuan + dOutYuan);
        del0(strTmp);
        strText += QString("\n合计报销金额为：%1元+%2元=%3元。\n    妥否，请领导批示。").arg(strIn, strOut, strTmp);
    }

//    if(strTitle.indexOf(QString("培训")) >= 0 && m_ini.strTrain.isEmpty() == false)
//    {
//        strText += "\n\n"+m_ini.strTrain;
//    }
//    else
//    {
//        if(! m_ini.strInternational_accredited.isEmpty() )
//        {
//            strText += "\n\n" + m_ini.strInternational_accredited;
//        }
//    }
    QString strWay;
    getWay(strTitle, strWay);
    m_pTextEdit->setText(strText+"\n\n"+strWay);
}

void QtReimDomestic_F::copyTitle()
{
    QString str = m_pDocTitle->text();
    copyStringToPaste(str);
}

void QtReimDomestic_F::copyShowEvent()
{
    QString str = m_pDocEvent->text();
    copyStringToPaste(str);
}

void QtReimDomestic_F::copyText()
{
    QString str = m_pTextEdit->toPlainText();
    copyStringToPaste(str);
}
