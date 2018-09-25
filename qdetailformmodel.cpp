#include "qdetailformmodel.h"
#include <QHBoxLayout>
#include "qttools.h"

#define DECIMAL(NUM) ((int)(((NUM)+0.005)*100))/100.0     //公文要求保留一位小数，同时因为double精度不够，需要+0.05

QDetailFormModel::QDetailFormModel(int nModel, QWidget *parent) : QWidget(parent)
{
    m_nModel = nModel;
    m_nDays = 0;
    m_pLabelTitle = new QtLabel();
    connect(m_pLabelTitle, SIGNAL(mouseClicked()), this, SLOT(doCopyLabelTitle()));
    QHBoxLayout * hLayout = new QHBoxLayout(this);
    switch(m_nModel)
    {
    case DEF_FORM_MODEL_LE:
    case DEF_FORM_MODEL_LE_F:
    case DEF_FORM_MODEL_LE_F_DAY:
        m_pLineEdit1 = new QtLineEdit();
        m_pLabelEdit1 = new QtLabel();
        m_pLineEdit2 = NULL;
        m_pLabelEdit2 = NULL;
        hLayout->addWidget(m_pLabelTitle,0);
        hLayout->addWidget(m_pLineEdit1,1);
        hLayout->addWidget(m_pLabelEdit1,2);
        connect(m_pLineEdit1, SIGNAL(textChanged(QString)), this, SLOT(changedSlot()));
        break;
    case DEF_FORM_MODEL_LEE:
        m_pLineEdit1 = new QtLineEdit();
        m_pLabelEdit1 = new QtLabel();
        m_pLineEdit2 = new QtLineEdit();
        m_pLabelEdit2 = new QtLabel();
        hLayout->addWidget(m_pLabelTitle,0);
        hLayout->addWidget(m_pLineEdit1,1);
        hLayout->addWidget(m_pLabelEdit1,2);
        hLayout->addWidget(m_pLineEdit2,3);
        hLayout->addWidget(m_pLabelEdit2,4);
        connect(m_pLineEdit1, SIGNAL(textChanged(QString)), this, SLOT(changedSlot()));
        connect(m_pLineEdit2, SIGNAL(textChanged(QString)), this, SLOT(days2Little(QString)));
                break;
    default:
        m_pLineEdit1 = NULL;
        m_pLabelEdit1 = NULL;
        m_pLineEdit2 = NULL;
        m_pLabelEdit2 = NULL;
        break;
    }
    setLayout(hLayout);
}

void QDetailFormModel::setWidgetTitle(QString strTitle, QString strLabelEdit1, QString strLabelEdit2)
{
    switch(m_nModel)
    {
    case DEF_FORM_MODEL_LE:
    case DEF_FORM_MODEL_LE_F:
    case DEF_FORM_MODEL_LE_F_DAY:
        m_pLabelTitle->setText(strTitle);
        m_pLabelEdit1->setText(strLabelEdit1);
        break;
    case DEF_FORM_MODEL_LEE:
        m_pLabelTitle->setText(strTitle);
        m_pLabelEdit1->setText(strLabelEdit1);
        m_pLabelEdit2->setText(strLabelEdit2);
    default:
        // do nothing
        break;
    }
}

void QDetailFormModel::getWidgetTitle(QString& strTitle, QString& strLabelEdit1, QString& strLabelEdit2)
{
    switch(m_nModel)
    {
    case DEF_FORM_MODEL_LE:
    case DEF_FORM_MODEL_LE_F:
    case DEF_FORM_MODEL_LE_F_DAY:
        strTitle = m_pLabelTitle->text();
        strLabelEdit1 = m_pLabelEdit1->text();
        strLabelEdit2.clear();
        break;
    case DEF_FORM_MODEL_LEE:
        strTitle = m_pLabelTitle->text();
        strLabelEdit1 = m_pLabelEdit1->text();
        strLabelEdit2 = m_pLabelEdit2->text();
        break;
    default:
        strTitle.clear();
        strLabelEdit1.clear();
        strLabelEdit2.clear();
        break;
    }
}

void QDetailFormModel::getLineEdit(QString& strLineEdit1, QString& strLineEdit2)
{
    switch(m_nModel)
    {
    case DEF_FORM_MODEL_LE:
    case DEF_FORM_MODEL_LE_F:
    case DEF_FORM_MODEL_LE_F_DAY:
        strLineEdit1 = m_pLineEdit1->text();
        strLineEdit2.clear();
        break;
    case DEF_FORM_MODEL_LEE:
        strLineEdit1 = m_pLineEdit1->text();
        strLineEdit2 = m_pLineEdit2->text();
        break;
    default:
        strLineEdit1.clear();
        strLineEdit2.clear();
        break;
    }
}

void QDetailFormModel::setDays(const int nDays)
{
    m_nDays = nDays;
}

void QDetailFormModel::setPerCount(const int nPerCount)
{
    m_nPerCount = nPerCount;
}

void QDetailFormModel::setLimitDays(const int nLimitDays)
{
    m_nLimitDays = nLimitDays;
}

void QDetailFormModel::setDiscount(const double dDiscount)
{
    m_dDiscount = dDiscount;
}

void QDetailFormModel::setExchangeRate(const double dExchangeRate)
{
    m_dExchangeRate = dExchangeRate;
}

void QDetailFormModel::setUnit_F(const  QString strUnit)
{
    m_strUnit = strUnit;
}

void QDetailFormModel::getText(QString &strText, double &dYuan)
{
    strText.clear();
    dYuan = 0;
    QString strTmp;
    switch(m_nModel)
    {
    case DEF_FORM_MODEL_LE:
        strTmp = m_pLineEdit1->text();
        del0(strTmp);
        strText += m_pLabelTitle->text().trimmed() + strTmp + m_pLabelEdit1->text();
        dYuan = m_pLineEdit1->text().toDouble();
        break;
    case DEF_FORM_MODEL_LEE:
        strTmp = m_pLineEdit1->text();
        del0(strTmp);
        strText += m_pLabelTitle->text().trimmed() + strTmp + m_pLabelEdit1->text();
        strText += "×";
        strTmp = m_pLineEdit2->text();
        del0(strTmp);
        strText += strTmp + m_pLabelEdit2->text();
        strText += "×";
        strText += QString::number(m_nPerCount) + "人";
        dYuan = m_pLineEdit1->text().toDouble() * m_pLineEdit2->text().toDouble() * m_nPerCount;
        strTmp = QString::number(dYuan, 'f');
        del0(strTmp);
        strText += "=" + strTmp + "元";
        break;
    case DEF_FORM_MODEL_LE_F:
    {
        strTmp = m_pLineEdit1->text();
        del0(strTmp);
        strText = QString("%1%2%3\n").arg(m_pLabelTitle->text().trimmed(), strTmp, m_pLabelEdit1->text());
        strText += QString("换成人民币为：");
        strTmp = m_pLineEdit1->text();
        del0(strTmp);
        dYuan = strTmp.toDouble();
        strText += strTmp + m_pLabelEdit1->text();
        strText += "×";
        QString strExchangeRate = QString::number(m_dExchangeRate);
        del0(strExchangeRate);
        dYuan = dYuan * m_dExchangeRate;
       dYuan  = DECIMAL(dYuan);
        strText += strExchangeRate + "=";
        strTmp = QString::number(dYuan);
        del0(strTmp);
        strText += strTmp + "元";
    }
        break;
    case DEF_FORM_MODEL_LE_F_DAY:
    {
        strText = m_pLabelTitle->text().trimmed();
        QString strExchangeRate = QString::number(m_dExchangeRate);
        del0(strExchangeRate);
        QString strDiscount = QString::number(m_dDiscount);
        del0(strDiscount);
        if( m_nDays > m_nLimitDays)
        {//超出限制天数的补贴，要打折
            strTmp = m_pLineEdit1->text();
            del0(strTmp);
//            strText += QString("%1%2×%3天×%4人+%5%6×%7天×%8×%9人 =")
//                    .arg(strTmp, m_pLabelEdit1->text(), QString::number(m_nLimitDays), QString::number(m_nPerCount),
//                         strTmp, m_pLabelEdit1->text(), QString::number(m_nDays-m_nLimitDays), strDiscount, QString::number(m_nPerCount));
            strText += QString("%1%2×%3天×%4人×%5 =")
                    .arg(strTmp, m_pLabelEdit1->text(), QString::number(m_nDays), QString::number(m_nPerCount), strDiscount);
            dYuan = strTmp.toDouble();
//            dYuan = dYuan * m_nLimitDays *m_nPerCount + dYuan * (m_nDays - m_nLimitDays)*m_dDiscount * m_nPerCount;
            dYuan = dYuan * m_nDays * m_nPerCount * m_dDiscount;
            dYuan  = DECIMAL(dYuan);
            strTmp = QString::number(dYuan);
            del0(strTmp);
            strText += strTmp+m_strUnit;
            strText += QString("\n换成人民币为：%1%2×%3=").arg(strTmp, m_strUnit, strExchangeRate);
            dYuan = dYuan * m_dExchangeRate;
            dYuan  = DECIMAL(dYuan);
            strTmp = QString::number(dYuan);
            del0(strTmp);
            strText += QString("%1元").arg(strTmp);
        }
        else
        {//未超出限制天数，所有补贴不打折
            strTmp = m_pLineEdit1->text();
            del0(strTmp);
            strText += QString("%1%2×%3天×%4人=")
                    .arg(strTmp, m_pLabelEdit1->text(), QString::number(m_nDays), QString::number(m_nPerCount));
            dYuan = strTmp.toDouble();
            dYuan = dYuan * m_nDays * m_nPerCount;
            dYuan  = DECIMAL(dYuan);
            strTmp = QString::number(dYuan);
            del0(strTmp);
            strText += strTmp+m_strUnit;
            strText += QString("\n换成人民币为：%1%2×%3=").arg(strTmp, m_strUnit, strExchangeRate);
            dYuan = dYuan * m_dExchangeRate;
            dYuan  = DECIMAL(dYuan);
            strTmp = QString::number(dYuan);
            del0(strTmp);
            strText += QString("%1元").arg(strTmp);
        }
    }
        break;
    default:
        strText.clear();
        dYuan = 0;
        break;
    }
}

QString QDetailFormModel::getText1()
{
    switch(m_nModel)
    {
    case DEF_FORM_MODEL_LE:
    case DEF_FORM_MODEL_LEE:
    case DEF_FORM_MODEL_LE_F:
    case DEF_FORM_MODEL_LE_F_DAY:
        return m_pLineEdit1->text();
        break;
    default:
        return "";
        break;
    }
    return "";
}

void QDetailFormModel::setText1(QString& str)
{
    switch(m_nModel)
    {
    case DEF_FORM_MODEL_LE:
    case DEF_FORM_MODEL_LE_F:
    case DEF_FORM_MODEL_LE_F_DAY:
    case DEF_FORM_MODEL_LEE:
        m_pLineEdit1->setText(str);
        break;
    default:
        break;
    }
}

QString QDetailFormModel::getText2()
{
    switch(m_nModel)
    {
    case DEF_FORM_MODEL_LE:
    case DEF_FORM_MODEL_LE_F:
    case DEF_FORM_MODEL_LE_F_DAY:
        return "";
        break;
    case DEF_FORM_MODEL_LEE:
        return m_pLineEdit2->text();
        break;
    default:
        return "";
        break;
    }
    return "";
}

void QDetailFormModel::setText2(QString& str)
{
    switch(m_nModel)
    {
    case DEF_FORM_MODEL_LE:
    case DEF_FORM_MODEL_LE_F:
    case DEF_FORM_MODEL_LE_F_DAY:
        break;
    case DEF_FORM_MODEL_LEE:
        m_pLineEdit1->setText(str);
        break;
    default:
        break;
    }
}
void QDetailFormModel::clearText()
{
    switch(m_nModel)
    {
    case DEF_FORM_MODEL_LE:
    case DEF_FORM_MODEL_LE_F:
    case DEF_FORM_MODEL_LE_F_DAY:
        m_pLineEdit1->clear();
        break;
    case DEF_FORM_MODEL_LEE:
        m_pLineEdit1->clear();
        m_pLineEdit2->clear();
        break;
    default:
        // do nothing
        break;
    }
    return ;
}

void QDetailFormModel::changedSlot()
{
    emit changed();
}

void QDetailFormModel::days2Little(const QString &strText)
{
    if(! m_pLineEdit2)
    {
        return ;
    }

    int nDays = strText.toInt();
    if(nDays > m_nDays)
    {
        m_pLineEdit2->setText(QString::number(m_nDays));
    }
    changedSlot();
}

void QDetailFormModel::doCopyLabelTitle()
{
    QString str = m_pLabelTitle->text();
    str.trimmed();
    str.chop(1);
    copyStringToPaste(str);
}

bool QDetailFormModel::isEmpt()
{
    bool bRet = true;
    switch(m_nModel)
    {
    case DEF_FORM_MODEL_LE:
    case DEF_FORM_MODEL_LE_F:
    case DEF_FORM_MODEL_LE_F_DAY:
        bRet = m_pLineEdit1->text().isEmpty();
        break;
    case DEF_FORM_MODEL_LEE:
        bRet = m_pLineEdit1->text().isEmpty() && m_pLineEdit2->text().isEmpty();
        break;
    default:
        bRet = true;
        break;
    }
    return bRet;
}
