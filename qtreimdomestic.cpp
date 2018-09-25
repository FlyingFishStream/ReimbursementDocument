#include "qtreimdomestic.h"
#include <QClipboard>
#include <QDate>

QtReimDomestic::QtReimDomestic(QWidget *parent)
    :QtPerInfoDlg(parent)
{
    setWindowTitle("国内报销");
    this->resize(680,900);
    m_pVerticalLayout = new QVBoxLayout();
    m_pHorizontalLayoutEvent = new QHBoxLayout() ;
    m_pHorizontalLayoutDocTitle = new QHBoxLayout() ;
    m_pHorizontalLayoutTicket = new QHBoxLayout();

    m_pLabelEvent = new QLabel();
    m_pLabelEvent->setText("报销事件");
    m_pLineEditEvent = new QtLineEdit();
    m_pLabelDocTitle = new QLabel();
    m_pLabelDocTitle->setText("出差公文");
    m_pLineEditDocTitle = new QtLineEdit();
    m_pDateCompute = new QDateCompute();
    m_pDForm = new QDetailForm();
    m_pLabelTitle = new QtLabel();
    m_pLabelShowEvent = new QtLabel();
    m_pTextEditText = new QtTextEdit();

    m_pGroupBoxTicket = new QGroupBox();
    QRadioButton* pRadioButton = NULL;
    m_verpRadioButtonTicket.clear();
    for(int i = 0;i < DEF_TICKETKIND; i++)
    {
        pRadioButton = new QRadioButton(m_pGroupBoxTicket);
        m_verpRadioButtonTicket.append(pRadioButton);
    }
    m_verpRadioButtonTicket[DEF_TICKETKIND_NO]->setText("未呈报机票");
    m_verpRadioButtonTicket[DEF_TICKETKIND_GO]->setText("已呈报去程机票");
    m_verpRadioButtonTicket[DEF_TICKETKIND_BACK]->setText("已呈报返回机票");
    m_verpRadioButtonTicket[DEF_TICKETKIND_GOBACK]->setText("已呈报往返机票");
    m_verpRadioButtonTicket[DEF_TICKETKIND_GOBACK]->setChecked(true);

    m_pHorizontalLayoutEvent->addWidget(m_pLabelEvent);
    m_pHorizontalLayoutEvent->addWidget(m_pLineEditEvent);
    for(int i = 0; i <DEF_TICKETKIND; i++)
    {
        m_pHorizontalLayoutTicket->addWidget(m_verpRadioButtonTicket[i]);
        connect(m_verpRadioButtonTicket[i], SIGNAL(toggled(bool)), this, SLOT(doText()));
    }
    m_pHorizontalLayoutDocTitle->addWidget(m_pLabelDocTitle);
    m_pHorizontalLayoutDocTitle->addWidget(m_pLineEditDocTitle);

    m_pVerticalLayout->addLayout(m_pHorizontalLayoutEvent);
    m_pVerticalLayout->addLayout(m_pHorizontalLayoutDocTitle);
    m_pVerticalLayout->addWidget(m_pDateCompute);
    m_pVerticalLayout->addLayout(m_pHorizontalLayoutTicket);
    m_pVerticalLayout->addWidget(m_pDForm);
    m_pVerticalLayout->addWidget(m_pLabelTitle);
    m_pVerticalLayout->addWidget(m_pLabelShowEvent);
    m_pVerticalLayout->addWidget(m_pTextEditText);

    ui.verticalLayout->addLayout(m_pVerticalLayout);
    setLayout(ui.verticalLayout);

    connect(m_pLineEditEvent, SIGNAL(textChanged(QString)), this, SLOT(setShowEvent()));
    connect(m_pLineEditDocTitle, SIGNAL(textChanged(QString)), this, SLOT(setShowEvent()));

    connect(m_pLabelTitle, SIGNAL(mouseClicked()), this, SLOT(copyTitle()));
    connect(m_pLabelShowEvent, SIGNAL(mouseClicked()), this, SLOT(copyShowEvent()));
    connect(m_pTextEditText, SIGNAL(mouseClicked()), this, SLOT(copyText()));

    connect(ui.lineEdit, SIGNAL(textChanged(QString)), this, SLOT(doText()));
    connect(m_pLineEditEvent, SIGNAL(textChanged(QString)), this, SLOT(doText()));
    connect(m_pDForm, SIGNAL(changed()), this, SLOT(doText()));
    connect(m_pLineEditDocTitle, SIGNAL(textChanged(QString)), this, SLOT(doText()));
    connect(m_pDateCompute, SIGNAL(changed()), this, SLOT(doText()));
}

void QtReimDomestic::addTicketString(QString &strText)
{
    for(int i = 0; i < DEF_TICKETKIND; i++)
    {
        if( m_verpRadioButtonTicket[i]->isChecked())
        {
            switch(i)
            {
            case DEF_TICKETKIND_NO:
                break;
            case DEF_TICKETKIND_GO:
                strText += "；\n去程机票由商旅网出票";
                break;
            case DEF_TICKETKIND_BACK:
                strText +="；\n返程机票由商旅网出票";
                break;
            case DEF_TICKETKIND_GOBACK:
                strText += "；\n往返机票由商旅网出票，公司月结";
                break;
            default:
                break;
            }
            break;
        }
    }
    strText += "。";
}

void QtReimDomestic::getEventFromDocTitle(QString &strText)
{
    strText.clear();
    strText = m_pLineEditDocTitle->text();
    int nBegin1 = strText.lastIndexOf("前往");
    int nBegin2 = strText.lastIndexOf("参加");
    int nBegin = nBegin1>0?nBegin1:nBegin2;
    strText = strText.right(strText.length()-nBegin);
    int nEnd = strText.lastIndexOf("的") ;
    strText = strText.left(nEnd);
}

void QtReimDomestic::setShowEvent()
{
    QString str;
    str.clear();
    if(m_pLineEditDocTitle->text().isEmpty() &&
            m_pLineEditEvent->text().isEmpty())
    {
        return ;
    }
    if(m_pLineEditDocTitle->text().isEmpty())
    {
        str = m_pLineEditEvent->text();
    }
    else
    {
        getEventFromDocTitle(str);
    }

    str += "。";

    m_pLabelShowEvent->setText(str);
    return ;
}

void QtReimDomestic::doText()
{
    if(m_pLineEditEvent->text().isEmpty() &&
            m_pLineEditDocTitle->text().isEmpty() )
    {
        m_pLineEditDocTitle->setDisabled(false);
        m_pLineEditEvent->setDisabled(false);
        return ;
    }
    else
    {
        if(m_pLineEditDocTitle->text().isEmpty())
            m_pLineEditDocTitle->setDisabled(true);
        else
            m_pLineEditEvent->setDisabled(true);
    }

    if( (! m_pDateCompute->getDateCompute()) ||
            ui.lineEdit->text().isEmpty())
    {
        return ;
    }

    int nDays = m_pDateCompute->getDateCompute();
    if(nDays > 0)
    {
        m_pDForm->setDays(nDays);
    }
    else
    {
        m_pLabelTitle->setText("");
        m_pTextEditText->setText("");
        return ;
    }

    QVector<Perinfo> vPerInfo;
    QString strTmp;
    QString strTitle;
    QString strText;

    strTitle.clear();
    strText.clear();

//    strTitle += "关于重庆基地";
//    strText += "各位领导:";
//    strText += "\n";
//    strText += "    现申请报销重庆基地";
    strTitle += "关于" + m_ini.strPlace;
    strText += "各位领导：\n    现申请报销"+m_ini.strWorkGroup;

    getPerInfoInfact(vPerInfo);
    if(vPerInfo.count() <= DEF_ZERO)
    {
        return ;
    }
    m_pDForm->setPerCount(vPerInfo.count());

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
            strText += "（";
            strText += vPerInfo[i].id;
            strText += "）";

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

    if(m_pLineEditDocTitle->text().isEmpty())
    {
        strTitle+=m_pLineEditEvent->text();
        strText += m_pLineEditEvent->text();
    }
    else
    {
        strTmp.clear();
        getEventFromDocTitle(strTmp);
        strTitle += strTmp;
        strText += strTmp;
        strTmp.clear();
    }

    strTitle += "的差旅费报销申请";
    m_pLabelTitle->setText(strTitle);

    strText += "的差旅费。";
    strText += "\n";

    strText += ui.lineEdit->text();
    strText += "共计出差";
    strText += QString ::number(m_pDateCompute->getDateCompute()) + "天(";
    if(m_pDateCompute->getDateCompute() == 1)
    {
        strText +=m_pDateCompute->getDate1().toString("yyyy.M.d");
    }
    else
    {
        strText +=m_pDateCompute->getDate1().toString("yyyy.M.d");
        strText += "-";
        strText +=m_pDateCompute->getDate2().toString("yyyy.M.d");
    }
    strText += "），报销明细如下：\n";

    if(m_pDForm->isEmpt())
    {
        return ;
    }

    strTmp.clear();
    m_pDForm->getText(strTmp);
    if(strTmp.isEmpty())
    {
        return ;
    }
    strText +=strTmp;
    /*无机票，去程由商旅出票 返程由商旅出票 往返机票由商旅出票 */
    addTicketString(strText);

    strText += "\n共计报销:";
    m_pDForm->getFormula(strTmp);
    strText += strTmp +"。";
    strText += "\n    妥否，呈请领导批示。";

//    if(strTitle.indexOf(QString("培训")) >= 0 && m_ini.strTrain.isEmpty() == false)
//    {
//        strText += "\n\n"+m_ini.strTrain;
//    }
//    else
//    {
//        if( strTitle.strAOG.indexOf(QString("AOG")) >= 0)
//        {
//            strText += "\n\n"+m_ini.strAOG;
//        }
//        else if( m_ini.strExpenses.isEmpty() == false)
//        {
//            strText += "\n\n"+m_ini.strExpenses;
//        }
//    }
    QString strWay;
    getWay(strTitle, strWay);
    m_pTextEditText->setText(strText+"\n\n"+strWay);
    return ;
}

void QtReimDomestic::copyTitle()
{
    QString str = m_pLabelTitle->text();
    copyStringToPaste(str);
}

void QtReimDomestic::copyShowEvent()
{
    QString str = m_pLabelShowEvent->text();
    copyStringToPaste(str);
}

void QtReimDomestic::copyText()
{
    QString str = m_pTextEditText->toPlainText();
    copyStringToPaste(str);
}
