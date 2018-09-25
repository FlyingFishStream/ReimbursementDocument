#include "data.h"
#include "qdetailform_f.h"
#include <QVBoxLayout>

QDetailForm_F::QDetailForm_F(QWidget *parent)
    : QWidget(parent)
{
    m_pKindle = new QDetailFormModel(DEF_FORM_MODEL_LE_F);
    m_pDFMTicket = new QDetailFormModel(DEF_FORM_MODEL_LE_F);
    m_pDFMFare = new QDetailFormModel(DEF_FORM_MODEL_LE_F);
    m_pDFMFood = new QDetailFormModel(DEF_FORM_MODEL_LE_F_DAY);
    m_pDFMTransportation = new QDetailFormModel(DEF_FORM_MODEL_LE_F);
    m_pDFMUnAccommodation = new QDetailFormModel(DEF_FORM_MODEL_LE_F_DAY);
    m_pDFMAccommodation = new QDetailFormModel(DEF_FORM_MODEL_LE_F);
    m_pDFMIncidental = new QDetailFormModel(DEF_FORM_MODEL_LE_F_DAY);
    m_pDFMTraining = new QDetailFormModel(DEF_FORM_MODEL_LE_F);

    m_verpModel.clear();
    m_verpModel.append(m_pKindle);
    m_verpModel.append(m_pDFMTicket);
    m_verpModel.append(m_pDFMFare);
    m_verpModel.append(m_pDFMFood);
    m_verpModel.append(m_pDFMTransportation);
    m_verpModel.append(m_pDFMUnAccommodation);
    m_verpModel.append(m_pDFMAccommodation);
    m_verpModel.append(m_pDFMIncidental);
    m_verpModel.append(m_pDFMTraining);

    m_pKindle->setWidgetTitle(QString("币种："));
    connect(m_pKindle, SIGNAL(changed()), this, SLOT(setWidgetTitles()));
    setWidgetTitles();

    QVBoxLayout* layout = new QVBoxLayout(this);
    for (int i = 0; i < m_verpModel.count(); i++)
    {
        layout->addWidget(m_verpModel[i]);
        connect(m_verpModel[i], SIGNAL(changed()), this, SLOT(changedSlot()));
    }
    setLayout(layout);
}

double QDetailForm_F::getText(QString &strText)
{
    QString strTmp;
    double dYuan,dTmp;
    int nCount = 0;
    dYuan = 0;
    strText.clear();
    for(int i = 1; i < m_verpModel.count(); i++)
    {
        m_verpModel[i]->getText(strTmp, dTmp);
        if( dTmp == 0 )
        {
            continue;
        }
        if(nCount != 0)
        {
            strText += ";\n";
        }
        strText += strTmp;
        dYuan += dTmp;
        nCount++;
    }
    return dYuan;
}

void QDetailForm_F::clearText()
{
    for(int i = 0; i < m_verpModel.count(); i++)
    {
        m_verpModel[i]->clearText();
    }
}

void QDetailForm_F::getFormula(QString &strText)
{
    strText.clear();
    int nCount = 0;
    double dYuan = 0;
    double dRet = 0;
    QString strTmp;

    for(int i = 1; i < m_verpModel.count(); i++)
    {
        m_verpModel[i]->getText(strTmp, dYuan);
        if( dYuan == 0)
        {
            continue ;
        }
        dRet += dYuan;
        if( nCount != 0)
        {
            strText += "+";
        }
        strTmp = QString::number(dYuan, 'f');
        del0(strTmp);
        strText += strTmp + "元";
        nCount ++;
    }

    if(nCount == 0)
    {
        strText.clear();
        return ;
    }
    if( nCount == 1)
    {
        // strText == XX元
        return ;
    }
    strTmp = QString::number(dRet, 'f');
    del0(strTmp);
    strText += "="+ strTmp +"元";
}

void QDetailForm_F::setDays(const int nDays)
{
    for(int i = 0; i < m_verpModel.count(); i++)
    {
        m_verpModel[i]->setDays(nDays);
    }
}

void QDetailForm_F::setLimitDays(const int nDays)
{
    for(int i = 0; i < m_verpModel.count(); i++)
    {
        m_verpModel[i]->setLimitDays(nDays);
    }
}

void QDetailForm_F::setDiscount(const double dDiscount)
{
    for(int i = 0; i < m_verpModel.count(); i++)
    {
        m_verpModel[i]->setDiscount(dDiscount);
    }
}

void QDetailForm_F::setExchangeRate(const double dExchangeRate)
{
    for(int i = 0; i < m_verpModel.count(); i++)
    {
        m_verpModel[i]->setExchangeRate(dExchangeRate);
    }
}
void QDetailForm_F::setUnit_F()
{
    for(int i = 0; i < m_verpModel.count(); i++)
    {
        m_verpModel[i]->setUnit_F( m_pKindle->getText1() );
    }
}

void QDetailForm_F::setPerCount(const int nPerCount)
{
    for(int i = 0; i < m_verpModel.count(); i++)
    {
        m_verpModel[i]->setPerCount(nPerCount);
    }
}
QString QDetailForm_F::getKindle()
{
    return m_pKindle->getText1();
}

void QDetailForm_F::changedSlot()
{
    emit changed();
}

void QDetailForm_F::setWidgetTitles()
{
    QString strKindle,strTmp;
    m_pKindle->getLineEdit(strKindle, strTmp);

    m_pDFMTicket->setWidgetTitle("      飞机票：",strKindle);
    m_pDFMFare ->setWidgetTitle("      车船费：",strKindle);
    m_pDFMFood->setWidgetTitle("        伙食：",QString("%1/天/人").arg(strKindle));
    m_pDFMTransportation->setWidgetTitle("  市内交通费：",strKindle);
    m_pDFMUnAccommodation->setWidgetTitle("无证住宿补贴：",QString("%1/天/人").arg(strKindle));
    m_pDFMAccommodation->setWidgetTitle("  有证住宿费：",strKindle);
    m_pDFMIncidental->setWidgetTitle("        杂费：",QString("%1/天/人").arg(strKindle));
    m_pDFMTraining->setWidgetTitle("      培训费：",strKindle);
}
