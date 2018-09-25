#include "qttools.h"
#include "data.h"
#include <QClipboard>
#include <QApplication>

int GetStringCount(const QString & strText,QString strSep)
{
    return strText.count(strSep);
}

QString GetStringIndex(const QString & strText, int nIndex, QString strSep)
{
    return strText.section(strSep,nIndex,nIndex);
}

void delBlank(QString &strs)
{
    int len = strs.length();
    for (int i=0;i<len; )
    {
        if (strs.at(i).isSpace())
        {
            strs.remove(i,1);
            len --;
            continue;
        }
        i++;
    }
}

void del0(QString &strText)
{
    int nIndex  = strText.lastIndexOf(".");
    int nLength = strText.length();

    if(nIndex <= 0)
    {
        return ;
    }

    while(nLength >= nIndex)
    {
        if(strText[nLength-1] != QChar('0'))
        {
            if(strText[nLength-1] == QChar('.'))
            {
                strText.remove(nLength-1,1);
            }
            return ;
        }

        strText = strText.remove(nLength-1,1);
        nLength = strText.length();
    }
}

void copyStringToPaste(const QString &strText)
{
    QClipboard *board = QApplication::clipboard();
    board->setText(strText);
}

void getStringFromPaste(QString &strText)
{
    QClipboard *board = QApplication::clipboard();
    board->text(strText);
}
