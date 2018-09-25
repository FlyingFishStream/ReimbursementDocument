#include "qtexcel.h"
#include <QDebug>
#include <QApplication>
#include <windows.h>
#include <QDir>

QtExcel::QtExcel(QString filepath)
{
    HRESULT r;
    r = OleInitialize(0);
    if (r != S_OK && r != S_FALSE)
    {
      qWarning("Qt: Could not initialize OLE (error %x)", (unsigned int)r);
    }
//    CoInitializeEx(NULL,COINIT_MULTITHREADED|COINIT_SPEED_OVER_MEMORY);

    initExcel();
    if(filepath != "")
    {
        setFileName(filepath);
    }
//    qDebug()<<QDir::current();
}

QtExcel::~QtExcel()
{
    // Deinitialize OLE/COM
    if(! m_excel)
    {
        delete m_excel;
        m_excel = NULL;
    }
    OleUninitialize();
}

void QtExcel::setFileName(QString file)
{
    if(! QFile::exists(file))
    {
        file = QApplication::applicationDirPath()+file;
        if(! QFile::exists(file))
        {
            qDebug()<<"file is not exists:"<<file;
        }
    }
    m_filename = file;
    qDebug()<<"m_filename:"<<m_filename;
}

QString QtExcel::getFileName()
{
    return m_filename;
}

bool QtExcel::open(QString filepath,int intSheet)
{
    if(! m_excel)
    {
        delete m_excel;
        m_excel = NULL;
    }
    m_excel = new QAxObject("Excel.Application",NULL);
    if(m_excel->isNull())
    {
        qDebug()<<"excel new error";
       return false;
    }

    m_excel->dynamicCall("SetVisible(bool)",false);
    m_workbooks = m_excel->querySubObject("WorkBooks");
    setFileName(filepath);
    m_workbook = m_workbooks->querySubObject("Open(QString,QVariant,QVariant)", m_filename,3,true);
    if(! m_workbook)
    {
        qDebug()<<"workbook open error.filename:"<<m_filename;
        return false;
    }
    m_sheets = m_workbook->querySubObject("Worksheets(int)", intSheet);
    if(! m_sheets)
    {
        qDebug()<<"m_sheets open error";
        return false;
    }
    return true;
}

//读取范围确定，然后循环输出
/*    QAxObject * worksheet = workbook->querySubObject("WorkSheets(int)", 1);//打开第一个sheet
    QAxObject * usedrange = worksheet->querySubObject("UsedRange");//获取该sheet的使用范围对象
    QAxObject * rows = usedrange->querySubObject("Rows");
    QAxObject * columns = usedrange->querySubObject("Columns");

    int intRowStart = usedrange->property("Row").toInt();
    int intColStart = usedrange->property("Column").toInt();
    int intCols = columns->property("Count").toInt();
    int intRows = rows->property("Count").toInt();

    for(int i=intRowstsrt;i <intRowStart + intRows;i++)
    {
        for(j=intColStart ;j<intColStrt+intCols;j++){
        {
            cell = worksheet->querySubObject("Cells(int,int)", i,j ); //获取单元格

            if(cell->property("Value").type()==QVariant::Double)
            {
                qDebug()<<QString::number(cell->property("Value").toDouble(),'f',0);
            }

            }else if(cell->property("Value").type()==QVariant::QString)
            {
                qDebug()<<cell->property("Value").toString();
            }
        }
    }
*/
bool QtExcel::read(int row,int col,QString &text)
{
    QAxObject* cell = NULL;
    if(! m_sheets)
    {
        qDebug()<<"m_sheets point NULL";
        return false;
    }
    cell = m_sheets->querySubObject("Cells(int,int)",row,col);
    if(! cell)
    {
        qDebug()<<"cell point NULL";
        return false;
    }
    text = cell->property("Value").toString();
    cell = NULL;
    return true;
}

bool QtExcel::write(int row, int col, const QString text)
{
    QAxObject* cell = NULL;
    if(! m_sheets)
    {
        qDebug()<<"m_sheets point NULL";
        return false;
    }
    cell = m_sheets->querySubObject("Cells(int,int)",row,col);
    if(! cell)
    {
        qDebug()<<"cell point NULL";
        return false;
    }
    if(! cell->setProperty("Value",text))
    {
        qDebug()<<"cell set value error";
        return false;
    }
    return true;
}
bool QtExcel::getUsedRange(UsedRange& usedrangs)
{
    if(! m_sheets)
    {
        return false;
    }
    QAxObject * usedrange = m_sheets->querySubObject("UsedRange");
    QAxObject * rows = usedrange->querySubObject("Rows");
    QAxObject * columns = usedrange->querySubObject("Columns");
    usedrangs.intRowStart = usedrange->property("Row").toInt();
    usedrangs.intColStart = usedrange->property("Column").toInt();
    usedrangs.intCols = columns->property("Count").toInt();
    usedrangs.intRows = rows->property("Count").toInt();
    qDebug("rowstart=%d,colstart=%d,row=%d,col=%d",
           usedrangs.intRowStart,usedrangs.intColStart,usedrangs.intRows,usedrangs.intCols);
    return true;
}

bool QtExcel::save()
{
    if(! m_workbook)
    {
        return false;
    }
    m_workbook->dynamicCall("Save()");
    return true;
}

bool QtExcel::saveAs(QString path)
{
    if(! m_workbook)
    {
        return false;
    }
    m_workbook->dynamicCall("SaveAs (QString)", path);
    return true;
}

bool QtExcel::close()
{
    if(! m_workbook)
    {
        qDebug()<<"close m_workbook NULL";
        return false;
    }
    m_workbook->dynamicCall("Close (Boolean)",false);
    m_excel->dynamicCall("Quit (void)");

    delete m_excel;
    initExcel();
    return true;
}

void QtExcel::initExcel()
{
    m_excel = NULL;
    m_workbooks = NULL;
    m_workbook = NULL;
    m_sheets = NULL;
    m_cell = NULL;
    m_filename = "";
}

