#ifndef QTTOOLS_H
#define QTTOOLS_H
#include "data.h"

void GetInfo(Iniinfo &iniinfo);
void SetInfo(Iniinfo &iniinfo);

int GetStringCount(const QString & strText, QString strSep = "、" );
QString GetStringIndex(const QString & strText, int nIndex, QString strSep = "、");
void delBlank(QString &strs);
void del0(QString &strText);
void copyStringToPaste(const QString &strText);
void getStringFromPaste(QString &strText);
#endif // QTTOOLS_H
