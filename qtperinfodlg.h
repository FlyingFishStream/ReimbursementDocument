#ifndef QTPERINFODLG_H
#define QTPERINFODLG_H

#include <QDialog>
#include <QStandardItemModel>
#include "data.h"
#include <QMutex>
#include "ui_qtperinfodlg.h"
#include "qteportstring.h"

class QtPerInfoDlg : public QDialog
{
    Q_OBJECT
public:
    explicit QtPerInfoDlg(QWidget *parent = 0);
    ~QtPerInfoDlg();
    void setPerInfo(QVector<Perinfo> verperinfo);
    void setIni(Iniinfo ini);
    void setEportString(QVector<Es> vecEs);
protected:
    void initTableView();
    void pushToTableView(const QVector<QString> vecStrName);
    void getPerInfoInfact(QVector<Perinfo> &verperinfo);
    bool findPerInfo(const QVector<QString> vecStrName, QVector<Perinfo> &vecPerInfo);
    void getWay(const QString strTitle, QString& strWay);
    QStandardItemModel* m_pModel;
    QVector<Perinfo> m_verperinfo;
    QVector<Es> m_vecEs;

private slots:
    void addTableView(QString strText);
    void addTableView();
    void copyToPaste(QModelIndex index);
    void delPerinfoTable();
protected:
    Iniinfo m_ini;
    Ui::QtPerInfoDlg ui;
};

#endif // QTPERINFODLG_H
