#include "qtticket.h"
#include "qttools.h"
#include <QTextEdit>
#include <QDate>
#include <QClipboard>
#include <QMessageBox>
#include <QTextCodec>
#include <QProcess>

QtTicket::QtTicket(QWidget *parent)
    :QtPerInfoDlg(parent)
{
    setWindowTitle("优惠机票公文");
    this->resize(QSize(700,420));
    m_pVerticalLayout = new QVBoxLayout();
    m_pHorizontaLayoutTicketKind = new QHBoxLayout();
    m_pHorizontalLayoutBTravel = new QHBoxLayout();
    m_pHorizontalLayoutBTEmail = new QHBoxLayout();
    m_pHorizontalLayoutTime = new QHBoxLayout();

    m_pGroupBox = new QGroupBox();

    m_pRBNo =new QRadioButton(m_pGroupBox);
    m_pRBGo = new QRadioButton(m_pGroupBox);
    m_pRBBack = new QRadioButton(m_pGroupBox);
    m_pRBGoBack = new QRadioButton(m_pGroupBox);
    m_pCheckBoxSeat = new QCheckBox();
    m_pRBGoBack->setChecked(true);
    m_pRBNo->setText("不申请机票");
    m_pRBGo->setText("去程");
    m_pRBBack->setText("返程");
    m_pRBGoBack->setText("往返机票");
    m_pCheckBoxSeat->setText("订座");

    m_pLabelBTravel = new QLabel();
    m_pLabelBTravel->setText("出差事由：");
    m_pLineEditBTravel = new QLineEdit();
    m_pLabelBTEmail = new QLabel();
    m_pLabelBTEmail->setText("出差邮件：");
    m_pLineEditBTEmail = new QLineEdit();

    m_pLabelTime = new QLabel();
    m_pLabelTime->setText("出差时间段");
    m_pLineEditTime1 = new QLineEdit();
    m_pLabelTimeTo = new QLabel();
    m_pLabelTimeTo->setText("——");
    m_pLineEditTime2 = new QLineEdit();

    m_pTLabel = new QtLabel();
    m_pTextEdit = new QtTextEdit();
    m_pTextEdit->resize(10,10);
    m_pLabelFinish = new QtLabel();
    m_pLabelFinish->setText("已交接。");
    m_pButtonFillPlanDocx = new QPushButton("生成出差日程规划表");

    m_pHorizontaLayoutTicketKind->addWidget(m_pRBNo);
    m_pHorizontaLayoutTicketKind->addWidget(m_pRBGo);
    m_pHorizontaLayoutTicketKind->addWidget((m_pRBBack));
    m_pHorizontaLayoutTicketKind->addWidget(m_pRBGoBack);
    m_pHorizontaLayoutTicketKind->addWidget(m_pCheckBoxSeat);

    m_pHorizontalLayoutBTravel->addWidget(m_pLabelBTravel);
    m_pHorizontalLayoutBTravel->addWidget(m_pLineEditBTravel);
    m_pHorizontalLayoutBTEmail->addWidget(m_pLabelBTEmail);
    m_pHorizontalLayoutBTEmail->addWidget(m_pLineEditBTEmail);

    m_pHorizontalLayoutTime->addWidget(m_pLabelTime);
    m_pHorizontalLayoutTime->addWidget(m_pLineEditTime1);
    m_pHorizontalLayoutTime->addWidget(m_pLabelTimeTo);
    m_pHorizontalLayoutTime->addWidget(m_pLineEditTime2);

    m_pVerticalLayout->addLayout(m_pHorizontaLayoutTicketKind);
    m_pVerticalLayout->addLayout(m_pHorizontalLayoutBTravel);
    m_pVerticalLayout->addLayout(m_pHorizontalLayoutBTEmail);
    m_pVerticalLayout->addLayout(m_pHorizontalLayoutTime);
    m_pVerticalLayout->addWidget(m_pTLabel);
    m_pVerticalLayout->addWidget(m_pTextEdit);
    m_pVerticalLayout->addWidget(m_pLabelFinish);
    m_pVerticalLayout->addWidget(m_pButtonFillPlanDocx);
    ui.verticalLayout->addLayout(m_pVerticalLayout);
    setLayout(ui.verticalLayout);

    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx);
    m_pLineEditTime1->setValidator(validator);
    m_pLineEditTime2->setValidator(validator);

    connect(m_pRBNo, SIGNAL(toggled(bool)), this, SLOT(doText()));
    connect(m_pRBGo, SIGNAL(toggled(bool)), this, SLOT(doText()));
    connect(m_pRBBack, SIGNAL(toggled(bool)), this, SLOT(doText()));
    connect(m_pRBGoBack, SIGNAL(toggled(bool)), this, SLOT(doText()));
    connect(m_pCheckBoxSeat, SIGNAL(toggled(bool)), this, SLOT(doText()));
    connect(m_pLineEditBTravel, SIGNAL(textChanged(QString)), this, SLOT(doText()));
    connect(m_pLineEditBTEmail, SIGNAL(textChanged(QString)), this, SLOT(doText()));
    connect(m_pLineEditTime1, SIGNAL(textEdited(QString)), this, SLOT(doText()));
    connect(m_pLineEditTime2, SIGNAL(textEdited(QString)), this, SLOT(doText()));
    connect(ui.lineEdit, SIGNAL(textChanged(QString)), this, SLOT(doText()));

    connect(m_pTLabel, SIGNAL(mouseClicked()), this, SLOT(copyTitle()));
    connect(m_pTextEdit, SIGNAL(mouseClicked()), this, SLOT(copyText()));
    connect(m_pLabelFinish, SIGNAL(mouseClicked()), this, SLOT(copyFinish()));

    connect(m_pButtonFillPlanDocx, SIGNAL(clicked(bool)), this, SLOT(fillPlanDocx()));
}

QtTicket::~QtTicket()
{

}

void QtTicket::doText()
{
    if( m_pLineEditBTravel->text().isEmpty() &&
            m_pLineEditBTEmail->text().isEmpty() )
    {
        m_pLineEditBTEmail->setDisabled(false);
        m_pLineEditBTravel->setDisabled(false);
    }
    else
    {
        if(m_pLineEditBTEmail->text().isEmpty())
            m_pLineEditBTEmail->setDisabled(true);
        else
            m_pLineEditBTravel->setDisabled(true);
    }

    if( (m_pLineEditBTravel->text().isEmpty() && m_pLineEditBTEmail->text().isEmpty()) ||
            m_pLineEditTime1->text().isEmpty() ||
            m_pLineEditTime2->text().isEmpty() ||
            ui.lineEdit->text().isEmpty())
    {
        return ;
    }
    QString text;QString title;
    text.clear();
    title.clear();

    QDate date1;QString strTime1;
    date1 = QDate::fromString(m_pLineEditTime1->text(),  "yyyyMMdd");
    QDate date2;QString strTime2;
    date2 = QDate::fromString(m_pLineEditTime2->text(), "yyyyMMdd");
    if( date1 < date2)
    {
        strTime1 = date1.toString( "yyyy年M月d日");
        strTime2 = date2.toString( "yyyy年M月d日");
        m_ini.DateGo = date1.toString("yyyy.M.d");
        m_ini.DateBack = date2.toString("yyyy.M.d");
    }
    else
    {
        strTime1 = date2.toString( "yyyy年M月d日");
        strTime2 = date1.toString( "yyyy年M月d日");
        m_ini.DateGo = date2.toString("yyyy.M.d");
        m_ini.DateBack = date1.toString("yyyy.M.d");
    }

    QString strNames = ui.lineEdit->text();
    int nPerCount;
    nPerCount = GetStringCount(strNames, "、")+1;

    text += "各位领导：\n    "+m_ini.strWorkGroup;
    text += strNames;
    title += "关于" + m_ini.strPlace + GetStringIndex(strNames, 0, "、");
//    title += "关于重庆基地"+GetStringIndex(strNames,0,"、");
    if(nPerCount > 1)
    {
        text += QString::number(nPerCount) + "人";
        title += "等"+QString::number(nPerCount)+"人";
    }

    if( strTime1 == strTime2)
    {
        text+= "将于"+strTime1;
        qDebug()<<"strTime1 ==strTime2:"<<strTime1;
    }
    else
    {
        text += "将于"+strTime1+"至"+strTime2;
    }

    if(! m_pLineEditBTravel->text().isEmpty())
    {
        title += m_pLineEditBTravel->text();
        text += m_pLineEditBTravel->text();
        m_ini.Thing = m_pLineEditBTravel->text();
    }
    else
    {
        int nCH = 0;
        int nEN = 0;
        title += "参加";
        QString tmp = m_pLineEditBTEmail->text();
        if(tmp.indexOf("上课通知") != -1)
        {
            tmp.remove(tmp.indexOf("上课通知"),4);
        }
        int nBegin = 0;
        nCH = tmp.lastIndexOf("：");
        nEN = tmp.lastIndexOf(":");
//        nBegin = tmp.lastIndexOf(":")>tmp.lastIndexOf("：")?:tmp.lastIndexOf(":"),tmp.lastIndexOf("：");
        nBegin = nCH>nEN?nCH:nEN;
        tmp = tmp.right(tmp.length()-nBegin-2).trimmed();
        int nEnd = 0;
        nCH = tmp.lastIndexOf("）");
        nEN = tmp.lastIndexOf(")");
//        nEnd = tmp.lastIndexOf(")")>tmp.lastIndexOf("）")?:tmp.lastIndexOf(")"),tmp.lastIndexOf("）");
        nEnd = nCH>nEN?nCH:nEN;
        tmp = tmp.left(nEnd+1);
        title += tmp;

        text +="参加";
        tmp = m_pLineEditBTEmail->text();
        nBegin = tmp.lastIndexOf("月");
        tmp=tmp.right(tmp.length()-nBegin-1).trimmed();
        nCH = tmp.lastIndexOf("）");
        nEN = tmp.lastIndexOf(")");
//        nEnd = tmp.lastIndexOf(")")>tmp.lastIndexOf("）")?tmp.lastIndexOf(")"):tmp.lastIndexOf("）");
        nEnd = nCH>nEN?nCH:nEN;
        tmp=tmp.left(nEnd+1);
        text += tmp;
        m_ini.Thing = tmp;
    }

    if(getTicketKind() == DEF_TICKETKIND_NO)
    {
        m_pCheckBoxSeat->setChecked(false);
    }

    switch(getTicketKind())
    {
    case DEF_TICKETKIND_NO:
        title += "的出差申请";
        text += "。现呈报出差公文。";
        break;
    case DEF_TICKETKIND_GO:
        title += "的去程公务优惠";
        text += "。现呈报去程公务优惠";
        break;
    case DEF_TICKETKIND_BACK:
        title += "的返程公务优惠";
        text += "。现呈报返程公务优惠";
        break;
    case DEF_TICKETKIND_GOBACK:
        title += "的往返公务优惠";
        text += "。现呈报往返公务优惠";
        break;
    default:
        // do nothing
        break;
    }

    if(getTicketKind() != DEF_TICKETKIND_NO)
    {
        if(m_pCheckBoxSeat->isChecked() )
        {
            title += "订座机票申请";
            text += "订座机票公文。";
        }
        else
        {
            title += "机票申请";
            text += "机票公文。";
        }
    }

    delBlank(title);
    m_pTLabel->setText(title);

    text += "\n";
    text += "    妥否，呈请领导批示。";
    m_pTextEdit->setText(text);

    QVector<Perinfo> verperinfo;
    getPerInfoInfact(verperinfo);

//        QMessageBox msgBox;
//        msgBox.setText( " verperinfo.count():"+QString::number(nPerCount)+"  "+QString::number(verperinfo.count()));
//        msgBox.exec();
    for(int i = 0 ; i < verperinfo.count(); i++)
    {
        if( i == 0 )
        {
            m_ini.Worker = verperinfo[i].name+","+verperinfo[i].level;
            continue;
        }
        m_ini.Worker += " ";
        m_ini.Worker += verperinfo[i].name+"," + verperinfo[i].level;
    }

    for(int i = 0; i < m_vecEs.count(); i++)
    {
        if( m_ini.Thing.indexOf( m_vecEs[i].strName ) > 0)
        {
            m_ini.PlaceDec = m_vecEs[i].strName;
            m_ini.PlaceDec_3 = m_vecEs[i].strEportstring;
            break;
        }
    }
    saveFillPlanDocxIni();
}

void QtTicket::saveFillPlanDocxIni()
{
    QSettings settings("Option.ini", QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("GBK"));

    settings.setValue("FillPlanDocx/Worker", m_ini.Worker);
    settings.setValue("FillPlanDocx/DateGo", m_ini.DateGo);
    settings.setValue("FillPlanDocx/DateBack", m_ini.DateBack);
    settings.setValue("FillPlanDocx/Thing", m_ini.Thing);
    settings.setValue("FillPlanDocx/PlaceDec", m_ini.PlaceDec);
    settings.setValue("FillPlanDocx/PlaceDec_3", m_ini.PlaceDec_3);
}

void QtTicket::copyTitle()
{
    QString str = m_pTLabel->text();
    copyStringToPaste(str);
}

void QtTicket::copyText()
{
    QString str = m_pTextEdit->toPlainText();
    copyStringToPaste(str);
}

void QtTicket::copyFinish()
{
    QString str = m_pLabelFinish->text();
    copyStringToPaste(str);
}

void QtTicket::fillPlanDocx()
{
    QProcess p(0);
//    p.setWorkingDirectory("");
    QString command = "python";
    QStringList args;
    args.append(m_ini.pythonfile);
    p.execute(command,args);
    return ;
}

int QtTicket::getTicketKind()
{
    if(m_pRBNo->isChecked())
    {
        return DEF_TICKETKIND_NO;
    }
    if(m_pRBGo->isChecked())
    {
        return DEF_TICKETKIND_GO;
    }
    if(m_pRBGoBack->isChecked())
    {
        return DEF_TICKETKIND_GOBACK;
    }
    if(m_pRBBack->isChecked())
    {
        return DEF_TICKETKIND_BACK;
    }
    return DEF_TICKETKIND_ERR;
}
