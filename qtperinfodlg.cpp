#include "qtperinfodlg.h"
#include "qttools.h"
#include <QApplication>
#include <QClipboard>
#include <QThread>


QtPerInfoDlg::QtPerInfoDlg(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
    setWindowTitle("人员信息");
    m_verperinfo.clear();

    m_pModel = new QStandardItemModel();
    ui.tableView->setModel(m_pModel);
    initTableView();
    setWindowFlags(Qt::WindowStaysOnTopHint);

    connect(ui.lineEdit, SIGNAL(textChanged(QString)), this, SLOT(addTableView(QString)));
    connect(ui.pbSearch, SIGNAL(clicked()), this, SLOT(addTableView()));
    connect(ui.tableView,SIGNAL(clicked(QModelIndex)), this, SLOT(copyToPaste(QModelIndex)));
    connect(ui.pbDel, SIGNAL(clicked()), this, SLOT(delPerinfoTable()));
}

QtPerInfoDlg::~QtPerInfoDlg()
{
    delete m_pModel;
}

void QtPerInfoDlg::setPerInfo(QVector<Perinfo> verperinfo)
{
    m_verperinfo = verperinfo;
    return ;
}

void QtPerInfoDlg::setIni(Iniinfo ini)
{
    m_ini.name = ini.name;
    m_ini.othername = ini.othername;
    m_ini.id = ini.id;
    m_ini.idcard = ini.idcard;
    m_ini.phone = ini.phone;
    m_ini.level = ini.level;
    m_ini.email = ini.email;
    m_ini.file = ini.file;
    m_ini.city = ini.city;
    m_ini.cityfile = ini.cityfile;
    m_ini.strPlace = ini.strPlace;
    m_ini.strWorkGroup = ini.strWorkGroup;
    m_ini.strExpenses = ini.strExpenses;
    m_ini.strTrain = ini.strTrain;
    m_ini.strInternational_accredited = ini.strInternational_accredited;
    m_ini.strAOG = ini.strAOG;
    m_ini.strFinanceFile = ini.strFinanceFile;
    m_ini.nLimitDays = ini.nLimitDays ;
    m_ini.dDiscount = ini.dDiscount;

    m_ini.pythonfile = ini.pythonfile;
    m_ini.docxSrc = ini.docxSrc;
    m_ini.docxDes = ini.docxDes;
    m_ini.Worker = ini.Worker;
    m_ini.DateGo =ini.DateGo;
    m_ini.DateBack =ini.DateBack;
    m_ini.Thing = ini.Thing;
    m_ini.PlaceSrc = ini.PlaceSrc;
    m_ini.PlaceSrc_3 = ini.PlaceSrc_3;
    m_ini.PlaceDec = ini.PlaceDec;
    m_ini.PlaceDec_3 = ini.PlaceDec_3;
}

void QtPerInfoDlg::setEportString(QVector<Es> vecEs)
{
    m_vecEs = vecEs;
}

void QtPerInfoDlg::addTableView(QString strText)
{
    QVector<QString> vecStrName;
    vecStrName.clear();
    initTableView();
    QString strName;

    QString::SectionFlag flag = QString::SectionDefault;
    for(int i = 0; i <= strText.count("、"); i++)
    {
//        qDebug()<<"strText.count:"<<strText.count("、")<<",Now i:"<<i;
        strName = strText.section("、",i,i,flag);
        vecStrName.push_back(strName);
//        qDebug()<<"===="<<"push to TableView:"<<strName;
    }
    pushToTableView(vecStrName);
    qDebug()<<"Finish addTableView:"<<strText;
}

void QtPerInfoDlg::addTableView()
{
    QString str = ui.lineEdit->text();
    addTableView(str);
}

void QtPerInfoDlg::copyToPaste(QModelIndex index)
{
    QString str = m_pModel->data(index).toString();
    QClipboard *board = QApplication::clipboard();

    board->setText(str);

    return ;
}

void QtPerInfoDlg::delPerinfoTable()
{
    int row = ui.tableView->currentIndex().row();
    if(row < 0)
    {
        return ;
    }
    m_pModel->removeRow(row);
}

void QtPerInfoDlg::initTableView()
{
    m_pModel->clear();
    m_pModel->setRowCount(DEF_ZERO);
    m_pModel->setHorizontalHeaderItem(DEF_HEAD_NAME,new QStandardItem("姓名"));
    m_pModel->setHorizontalHeaderItem(DEF_HEAD_OTHERNAME,new QStandardItem("别名"));
    m_pModel->setHorizontalHeaderItem(DEF_HEAD_ID,new QStandardItem("员工ID"));
    m_pModel->setHorizontalHeaderItem(DEF_HEAD_IDCARD,new QStandardItem("身份证"));
    m_pModel->setHorizontalHeaderItem(DEF_HEAD_PHONE,new QStandardItem("电话"));
    m_pModel->setHorizontalHeaderItem(DEF_HEAD_LEVEL,new QStandardItem("岗位"));
    m_pModel->setHorizontalHeaderItem(DEF_HEAD_EMAIL, new QStandardItem("邮件"));
    m_pModel->setHorizontalHeaderItem(DEF_HEAD_ACCOUNT, new QStandardItem("账号"));

    ui.tableView->setColumnWidth(DEF_HEAD_NAME,70);
    ui.tableView->setColumnWidth(DEF_HEAD_OTHERNAME,70);
    ui.tableView->setColumnWidth(DEF_HEAD_IDCARD,140);
    ui.tableView->setColumnWidth(DEF_HEAD_EMAIL,180);
    ui.tableView->setColumnWidth(DEF_HEAD_ACCOUNT,70);

    return ;
}

void QtPerInfoDlg::pushToTableView(const QVector<QString> vecStrName)
{
    QVector<Perinfo> vecPerInfo;
    vecPerInfo.clear();

    if(! findPerInfo(vecStrName, vecPerInfo))
    {
        qDebug()<<"can not find strName"<<vecStrName;
        return ;
    }

    for(int i =0; i < vecPerInfo.count(); i++)
    {
        m_pModel->setItem(i, DEF_HEAD_NAME,new QStandardItem(vecPerInfo[i].name));
        if(vecPerInfo[i].name != vecPerInfo[i].othername)
        {
            m_pModel->setItem(i, DEF_HEAD_OTHERNAME,new QStandardItem(vecPerInfo[i].othername));
        }
        else
        {
            m_pModel->setItem(i, DEF_HEAD_OTHERNAME,new QStandardItem(QString("")));;
        }
        m_pModel->setItem(i, DEF_HEAD_ID,new QStandardItem(vecPerInfo[i].id));
        m_pModel->setItem(i, DEF_HEAD_IDCARD,new QStandardItem(vecPerInfo[i].idcard));
        m_pModel->setItem(i, DEF_HEAD_PHONE,new QStandardItem(vecPerInfo[i].phone));
        m_pModel->setItem(i, DEF_HEAD_LEVEL,new QStandardItem(vecPerInfo[i].level));
        m_pModel->setItem(i, DEF_HEAD_EMAIL,new QStandardItem(vecPerInfo[i].email));
        m_pModel->setItem(i, DEF_HEAD_ACCOUNT,new QStandardItem(vecPerInfo[i].email.remove("@hnair.com")));
    }
}

void QtPerInfoDlg::getPerInfoInfact(QVector<Perinfo> &verperinfo)
{
    int nCount = m_pModel->rowCount();
    verperinfo.clear();
    Perinfo perinfo;
    for(int i = 0; i < nCount; i++)
    {
        perinfo.name = m_pModel->item(i,DEF_HEAD_NAME)->text();
        perinfo.othername = m_pModel->item(i,DEF_HEAD_OTHERNAME)->text();
        perinfo.id = m_pModel->item(i, DEF_HEAD_ID)->text();
        perinfo.idcard = m_pModel->item(i, DEF_HEAD_IDCARD)->text();
        perinfo.email = m_pModel->item(i, DEF_HEAD_EMAIL)->text();
        perinfo.phone = m_pModel->item(i, DEF_HEAD_PHONE)->text();
        perinfo.level = m_pModel->item(i, DEF_HEAD_LEVEL)->text();

        verperinfo.push_back(perinfo);
    }
}

bool QtPerInfoDlg::findPerInfo(const QVector<QString> vecStrName,QVector<Perinfo> &vecPerInfo)
{
    bool bRet = false;
    for(int i = 0; i < vecStrName.count(); i++)
    {
        for(int j = 0; j < m_verperinfo.count(); j++)
        {
            if(vecStrName[i] == m_verperinfo[j].name)
            {
                vecPerInfo.push_back(m_verperinfo[j]);
                bRet = true;
            }
        }
    }
    return bRet;
}

 void QtPerInfoDlg::getWay(const QString strTitle, QString& strWay)
 {
     strWay.clear();

     if(strTitle.indexOf(QString("培训")) >= 0 && m_ini.strTrain.isEmpty() == false)
     {
         strWay += m_ini.strTrain;
     }
     else
     {
         if( strTitle.indexOf(QString("AOG")) >= 0)
         {
             strWay += m_ini.strAOG;
         }
         else if( m_ini.strExpenses.isEmpty() == false)
         {
             strWay += m_ini.strExpenses;
         }
     }
 }
