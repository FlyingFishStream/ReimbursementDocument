#include "mainwindow.h"
#include "qdatecompute.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "qtexcel.h"
#include "qttools.h"
#include <QVariant>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initIni();
    qDebug()<<"finish init ini";
//    initCity();
//    qDebug()<<"finish init city";
    initPerInfo();
    qDebug()<<"finish init perinfo";
    connect(ui->pbOffcialTicket, SIGNAL(clicked(bool)), this, SLOT(offcialTicketDlg()));
    connect(ui->pbReimDomestic, SIGNAL(clicked(bool)), this, SLOT(reimDomesticDlg()));
    connect(ui->pbReimDomestic_F, SIGNAL(clicked(bool)), this, SLOT(reimDomesticDlg_F()));
    connect(ui->pbPerInfo, SIGNAL(clicked(bool)), this, SLOT(perInfoDlg()));
    connect(ui->pbWorkCalendar, SIGNAL(clicked(bool)), SLOT(workCalender()));
    connect(ui->pbDateCompute, SIGNAL(clicked(bool)), this, SLOT(dateCompute()));
    connect(ui->pbEportString, SIGNAL(clicked(bool)), this, SLOT(eportString()));

    m_pTicket = new QtTicket();
    m_pTicket->setPerInfo(m_verperinfo);
    m_pTicket->setIni(m_ini);

    m_pReimDomestic = new QtReimDomestic();
    m_pReimDomestic->setPerInfo(m_verperinfo);
    m_pReimDomestic->setIni(m_ini);

    m_pReimDomestic_F = new QtReimDomestic_F();
    m_pReimDomestic_F->setPerInfo(m_verperinfo);
    m_pReimDomestic_F->setIni(m_ini);
    m_pReimDomestic_F->init();

    m_pPerInfoDlg = new QtPerInfoDlg();
    m_pPerInfoDlg->setPerInfo(m_verperinfo);
    m_pPerInfoDlg->setIni(m_ini);

    m_pWorkCalender = new QtWorkCalender();
    m_pEportString = new QtEportString();
    m_pEportString->setIni(m_ini);
    m_pEportString->setESFile(m_ini.esFile);
    m_pEportString->init();

    m_pTicket->setEportString( m_pEportString->getEportString() );
}

MainWindow::~MainWindow()
{
    delete m_pPerInfoDlg;
    delete m_pTicket;
    delete m_pWorkCalender;
    delete m_pReimDomestic;
    delete ui;
}

void MainWindow::perInfoDlg()
{
    setWindowState(Qt::WindowMinimized);
    if(m_pPerInfoDlg)
    {
        m_pPerInfoDlg->show();
    }
    return ;
}

void MainWindow::reimDomesticDlg()
{
    setWindowState(Qt::WindowMinimized);
    if(m_pReimDomestic)
    {
        m_pReimDomestic->show();
    }
    return ;
}

void MainWindow::reimDomesticDlg_F()
{
    setWindowState(Qt::WindowMinimized);
    if(m_pReimDomestic_F)
    {
        m_pReimDomestic_F->show();
    }
}

void MainWindow::offcialTicketDlg()
{
    setWindowState(Qt::WindowMinimized);
    if(m_pTicket)
    {
        m_pTicket->show();
    }
    return ;
}

void MainWindow::dateCompute()
{
    QDialog dlg;
    QDateCompute date;
    QHBoxLayout  layout;

    layout.addWidget(&date);
    dlg.setWindowTitle("出差天数计算器");
    dlg.setLayout(&layout);
    dlg.exec();

    return ;
}

void MainWindow::eportString()
{
    setWindowState(Qt::WindowMinimized);
    if(m_pEportString)
    {
        m_pEportString->show();
    }
}

void MainWindow::workCalender()
{
    setWindowState(Qt::WindowMinimized);
    if(m_pWorkCalender)
    {
        m_pWorkCalender->showDay();
        m_pWorkCalender->show();
    }
}

void MainWindow::initIni()
{
    QSettings settings("Option.ini", QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("GBK"));
    qDebug()<<"ini file address :"<<settings.fileName();

    m_ini.file = settings.value("PersonInfo/file").toString();
    qDebug()<<"m_ini.file:"<<m_ini.file;

    m_ini.name = settings.value("PersonInfo/name").toInt();
    qDebug()<<"m_ini.name:"<<m_ini.name;

    m_ini.othername = settings.value("PersonInfo/othername").toInt();
    qDebug()<<"m_ini.othername:"<<m_ini.othername;

    m_ini.id = settings.value("PersonInfo/id").toInt();
    qDebug()<<"m_ini.id:"<<m_ini.id;

    m_ini.idcard = settings.value("PersonInfo/idcard").toInt();
    qDebug()<<"m_ini.idcard:"<<m_ini.idcard;

    m_ini.phone = settings.value("PersonInfo/phone").toInt();
    qDebug()<<"m_ini.phone:"<<m_ini.phone;

    m_ini.level = settings.value("PersonInfo/level").toInt();
    qDebug()<<"m_ini.level:"<<m_ini.level;

    m_ini.email = settings.value("PersonInfo/email").toInt();
    qDebug()<<"m_ini.email:"<<m_ini.email;

    m_ini.city = settings.value("City/city").toInt();
    qDebug()<<"m_ini.city:"<<m_ini.city;

    m_ini.cityfile = settings.value("City/file").toString();
    qDebug()<<"m_ini.cityfile:"<<m_ini.cityfile;

    m_ini.strPlace = settings.value("Document/place").toString();
    qDebug()<<"m_ini.strPlace:"<<m_ini.strPlace;

    m_ini.strWorkGroup = settings.value("Document/workgroup").toString();
    qDebug()<<"m_ini.strWorkGroup:"<<m_ini.strWorkGroup;

    m_ini.esFile = settings.value("EportString/file").toString();
    qDebug()<<"m_ini.esFile:"<<m_ini.esFile;

    m_ini.esProvince = settings.value("EportString/province").toInt();
    qDebug()<<"m_ini.esProvince:"<<m_ini.esProvince;

    m_ini.esName = settings.value("EportString/name").toInt();
    qDebug()<<"m_ini.esName:"<<m_ini.esName;

    m_ini.esAirport = settings.value("EportString/airport").toInt();
    qDebug()<<"m_ini.esAirport:"<<m_ini.esAirport;

    m_ini.esEportstring = settings.value("EportString/eportstring").toInt();
    qDebug()<<"m_ini.esEportstring:"<<m_ini.esEportstring;

    m_ini.strExpenses = settings.value("Submit/Expenses").toString();
    qDebug()<<"m_ini.strExpenses:"<<m_ini.strExpenses;

    m_ini.strTrain = settings.value("Submit/Train").toString();
    qDebug()<<"m_ini.strTrain:"<<m_ini.strTrain;

    m_ini.strInternational_accredited = settings.value("Submit/International_accredited").toString();
    qDebug()<<"m_ini.strInternational_accredited:"<<m_ini.strInternational_accredited;

    m_ini.strAOG = settings.value("Submit/AOG").toString();
    qDebug()<<"m_ini.AOG:"<<m_ini.strAOG;

    m_ini.strFinanceFile = settings.value("Submit/FinanceFile").toString();
    qDebug()<<"m_ini.strFinanceFile:"<<m_ini.strFinanceFile;

    m_ini.nLimitDays = settings.value("Submit/LimitDays").toInt();
    qDebug()<<"m_ini.nLimitDays:"<<m_ini.nLimitDays;

    m_ini.dDiscount = settings.value("Submit/Discount").toDouble();
    qDebug()<<"m_ini.dDiscount:"<<m_ini.dDiscount;

    m_ini.pythonfile = settings.value("FillPlanDocx/pythonfile").toString();
    qDebug()<<"m_ini.pythonfile:"<<m_ini.pythonfile;

    m_ini.docxSrc = settings.value("FillPlanDocx/docxSrc").toString();
    qDebug()<<"m_ini.docxSrc:"<<m_ini.docxSrc;

    m_ini.docxDes = settings.value("FillPlanDocx/docxDes").toString();
    qDebug()<<"m_ini.docxDes:"<<m_ini.docxDes;

    m_ini.Worker = settings.value("FillPlanDocx/Worker").toString();
    qDebug()<<"m_ini.Worker:"<<m_ini.Worker;

    m_ini.DateGo = settings.value("FillPlanDocx/DateGo").toString();
    qDebug()<<"m_ini.DateGo:"<<m_ini.DateGo;

    m_ini.DateBack = settings.value("FillPlanDocx/DateBack").toString();
    qDebug()<<"m_ini.DateBack:"<<m_ini.DateBack;

    m_ini.Thing = settings.value("FillPlanDocx/Thing").toString();
    qDebug()<<"m_ini.Thing:"<<m_ini.Thing;

    m_ini.PlaceSrc = settings.value("FillPlanDocx/PlaceSrc").toString();
    qDebug()<<"m_ini.PlaceSrc:"<<m_ini.PlaceSrc;

    m_ini.PlaceSrc_3 = settings.value("FillPlanDocx/PlaceSrc_3").toString();
    qDebug()<<"m_ini.PlaceSrc_3:"<<m_ini.PlaceSrc_3;

    m_ini.PlaceDec = settings.value("FillPlanDocx/PlaceDec").toString();
    qDebug()<<"m_ini.PlaceDec:"<<m_ini.PlaceDec;

    m_ini.PlaceDec_3 = settings.value("FillPlanDocx/PlaceDec_3").toString();
    qDebug()<<"m_ini.PlaceDec_3:"<<m_ini.PlaceDec_3;
}

bool MainWindow::initCity()
{
    QtExcel excel;
    UsedRange usedrange;
    memset(&usedrange,0,sizeof(usedrange));

    QString strCity;
    m_verCity.clear();

    if(! excel.open(m_ini.cityfile))
    {
        qDebug()<<"open file failed";
        return false;
    }

    if(! excel.getUsedRange(usedrange))
    {
        return false;
    }

    for(int row = usedrange.intRowStart; row < usedrange.intRowStart+usedrange.intRows; row++)
    {
        strCity = "";
        if(! excel.read(row, m_ini.city, strCity))
        {
            return false;
        }
        m_verCity.push_back(strCity);
    }
    excel.close();
    return true;
}

bool MainWindow::initPerInfo()
{
    QtExcel excel;

    UsedRange usedrange;
    memset(&usedrange,0,sizeof(usedrange));

    Perinfo perinfo;
    m_verperinfo.clear();

    if(! excel.open(m_ini.file))
    {
        return false;
    }

    if(! excel.getUsedRange(usedrange))
    {
        return false;
    }

    for(int row = usedrange.intRowStart; row < usedrange.intRowStart+usedrange.intRows; row++)
    {
        if(m_ini.id)
        {
            excel.read(row, m_ini.id, perinfo.id);
        }
        if(m_ini.name)
        {
            excel.read(row,m_ini.name, perinfo.name);
        }
        if(m_ini.othername)
        {
            excel.read(row,m_ini.othername, perinfo.othername);
        }
        if(m_ini.idcard)
        {
            excel.read(row, m_ini.idcard, perinfo.idcard);
        }
        if(m_ini.level)
        {
            excel.read(row, m_ini.level, perinfo.level);
        }
        if(m_ini.phone)
        {
            excel.read(row, m_ini.phone, perinfo.phone);
        }
        if(m_ini.email)
        {
            excel.read(row, m_ini.email, perinfo.email);
        }
        m_verperinfo.push_back(perinfo);
    }
    excel.close();
    return true;
}
