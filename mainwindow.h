#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "qtperinfodlg.h"
#include "qtticket.h"
#include "qtreimdomestic.h"
#include "qtreimdomestic_f.h"
#include "data.h"
#include "qtworkcalender.h"
#include "qteportstring.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void initIni();
    bool initCity();
    bool initPerInfo();
private:
    Iniinfo m_ini;
    QVector<Perinfo> m_verperinfo;
    QVector<QString> m_verCity;
    QtTicket *m_pTicket;
    QtReimDomestic* m_pReimDomestic;
    QtReimDomestic_F* m_pReimDomestic_F;
    QtPerInfoDlg* m_pPerInfoDlg;
    QtWorkCalender* m_pWorkCalender;
    QtEportString* m_pEportString;
private slots:
    void perInfoDlg();
    void reimDomesticDlg();
    void reimDomesticDlg_F();
    void offcialTicketDlg();
    void dateCompute();
    void eportString();
    void workCalender();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
