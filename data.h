#ifndef DATA_H
#define DATA_H

#include <QString>
#include <QSettings>
#include <QDebug>
#include <QVector>

#define DEF_ZERO                                        0
#define DEF_HEAD_NAME                          0
#define DEF_HEAD_OTHERNAME              1
#define DEF_HEAD_ID                                  2
#define DEF_HEAD_IDCARD                       3
#define DEF_HEAD_PHONE                        4
#define DEF_HEAD_LEVEL                          5
#define DEF_HEAD_ACCOUNT                    6
#define DEF_HEAD_EMAIL                          7

#define DEF_TICKETKIND_ERR                 -1
#define DEF_TICKETKIND_NO                   0
#define DEF_TICKETKIND_GO                   1
#define DEF_TICKETKIND_BACK              2
#define DEF_TICKETKIND_GOBACK        3
#define DEF_TICKETKIND                           4

typedef struct iniiinfo
{
    //[PersonInfo]
    int name;
    int othername;
    int id;
    int idcard;
    int phone;
    int level;
    int email;
    QString file;
    //[City]
    int city;
    QString cityfile;
    //[Document]
    QString strPlace;
    QString strWorkGroup;
    //[EportString]
    QString esFile;
    int esProvince;
    int esName;
    int esAirport;
    int esEportstring;
    //[Submit]
    QString strExpenses;
    QString strTrain;
    QString strInternational_accredited;
    QString strAOG;
    QString strFinanceFile;
    int nLimitDays;
    double dDiscount;
    //[FillPlanDocx]
    QString pythonfile;
    QString docxSrc;
    QString docxDes;
    QString Worker;
    QString DateGo;
    QString DateBack;
    QString Thing;
    QString PlaceSrc;
    QString PlaceSrc_3;
    QString PlaceDec;
    QString PlaceDec_3;
}Iniinfo,*pIniinfo;

typedef struct perinfo
{
    QString name;
    QString othername;
    QString id;
    QString idcard;
    QString phone;
    QString level;
    QString email;
}Perinfo,*pPerinfo;

//QVector<Perinfo> verperinfo;


#define SUCCESS 10240
#define FIALED  10241

#define DATEFORMAT  "yyyyMMdd"
#define DATESHOWFORMAT  "yyyy.M.d"
#define DATECHNFORMAT "yyyy年M月d日"

#include "qttools.h"
#endif // DATA_H
