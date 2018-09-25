#ifndef QTEXCEL_H
#define QTEXCEL_H
#include <QAxObject>
typedef struct usedrangs
{
    int intRows;
    int intCols;
    int intRowStart;
    int intColStart;
}UsedRange,*pUsedRange;

class QtExcel
{
public:
    QtExcel(QString filepath = "");
    ~QtExcel();
    void setFileName(QString file);
    QString getFileName();
    bool open(QString filepath, int intSheet=1);
    bool read(int row,int col,QString &text);
    bool write(int row, int col, const QString text);
    bool getUsedRange(UsedRange& usedrangs);
    bool save();
    bool saveAs(QString path);
    bool close();
private:
    void initExcel();
private:
    QAxObject* m_axobject;
    QAxObject* m_excel;
    QAxObject* m_workbooks;
    QAxObject* m_workbook;
    QAxObject* m_sheets;
    QString m_filename;
    QAxObject* m_cell;
};

#endif // QTEXCEL_H
