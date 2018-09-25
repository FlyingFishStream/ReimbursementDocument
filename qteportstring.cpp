#include "qteportstring.h"
#include <QDebug>

QtEportString::QtEportString()
{
    ui.setupUi(this);
    m_pExcel = new QtExcel();
    m_strFilePath = "";
    vecEs.clear();
    ui.label->setText("输入要查找的内容：");
    ui.pbDel->setVisible(false);
    this->setWindowTitle("三字码查询");

    m_pModel = new QStandardItemModel();
    ui.tableView->setModel(m_pModel);
    setWindowFlags(Qt::WindowStaysOnTopHint);

    connect(ui.pbSearch, SIGNAL(clicked(bool)), this, SLOT(onSearch()));
    connect(ui.lineEdit, SIGNAL(textChanged(QString)), this, SLOT(onSearch()));
}
void QtEportString::init()
{
    if(m_strFilePath == "")
    {
        return ;
    }
    vecEs.clear();
    if(! m_pExcel->open(m_strFilePath))
    {
        return ;
    }
    UsedRange usedRange;
    m_pExcel->getUsedRange(usedRange);
    QString tmp;
    Es esTmp;
    for(int i = usedRange.intRowStart; i < usedRange.intRowStart + usedRange.intRows; i++)
    {
        m_pExcel->read(i, m_ini.esProvince,esTmp.strProvnce);
        m_pExcel->read(i, m_ini.esName, esTmp.strName);
        m_pExcel->read(i, m_ini.esAirport, esTmp.strAirport);
        m_pExcel->read(i, m_ini.esEportstring, esTmp.strEportstring);
        vecEs.append(esTmp);
    }
    m_pExcel->close();
}

void QtEportString::setESFile(const QString& filePath)
{
    m_strFilePath = filePath;
}

void QtEportString::setIni(Iniinfo& ini)
{
    m_ini.esFile = ini.esFile;
    m_ini.esProvince = ini.esProvince;
    m_ini.esName = ini.esName;
    m_ini.esAirport = ini.esAirport;
    m_ini.esEportstring = ini.esEportstring;
}

void QtEportString::initTableView()
{
    m_pModel->clear();
    m_pModel->setRowCount(DEF_ZERO);
    m_pModel->setHorizontalHeaderItem(m_ini.esProvince-1,new QStandardItem(vecEs[0].strProvnce));
    m_pModel->setHorizontalHeaderItem(m_ini.esName-1,new QStandardItem(vecEs[0].strName));
    m_pModel->setHorizontalHeaderItem(m_ini.esAirport-1,new QStandardItem(vecEs[0].strAirport));
    m_pModel->setHorizontalHeaderItem(m_ini.esEportstring-1,new QStandardItem(vecEs[0].strEportstring));
}

QVector<Es> QtEportString::getEportString()
{
    return vecEs;
}

void QtEportString::onSearch()
{
    int nCount = 0;
    QString strSearch = ui.lineEdit->text();
    strSearch = strSearch.toUpper();

    initTableView();
    for(int i = 0; i < vecEs.count(); i++)
    {
        if(vecEs[i].strProvnce.indexOf(strSearch) >= DEF_ZERO ||
                vecEs[i].strName.indexOf(strSearch) >= DEF_ZERO ||
                vecEs[i].strAirport.indexOf(strSearch) >= DEF_ZERO ||
                vecEs[i].strEportstring.indexOf(strSearch) >= DEF_ZERO)
        {
            nCount = m_pModel->rowCount();
            m_pModel->setItem(nCount,m_ini.esProvince-1, new QStandardItem(vecEs[i].strProvnce));
            m_pModel->setItem(nCount,m_ini.esName-1, new QStandardItem(vecEs[i].strName));
            m_pModel->setItem(nCount,m_ini.esAirport-1, new QStandardItem(vecEs[i].strAirport));
            m_pModel->setItem(nCount,m_ini.esEportstring-1, new QStandardItem(vecEs[i].strEportstring));
        }
    }
}
