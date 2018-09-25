#ifndef QTEPORTSTRING_H
#define QTEPORTSTRING_H

#include <QDialog>
#include <QFile>
#include "qtexcel.h"
#include "data.h"
#include "ui_qtperinfodlg.h"
#include <QStandardItemModel>

typedef struct node
{
    QString strProvnce;
    QString strName;
    QString strAirport;
    QString strEportstring;
}Es,*pEs;

class QtEportString:public QDialog
{
    Q_OBJECT
public:
    QtEportString();
    void init();
    void setESFile(const QString& filePath);
    void setIni(Iniinfo& ini);
    void initTableView();
    QVector<Es> getEportString();
private:
    QtExcel* m_pExcel;
    QString m_strFilePath;
    QVector<Es> vecEs;
    Iniinfo m_ini;
    Ui::QtPerInfoDlg ui;
    QStandardItemModel* m_pModel;
private slots:
    void onSearch();
};

#endif // QTEPORTSTRING_H
