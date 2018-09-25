#include "qdetailform.h"
#include <QVBoxLayout>

QDetailForm::QDetailForm(QWidget *parent) : QWidget(parent)
{
    m_verpModel.clear();
    m_pDFMTicket = new QDetailFormModel();
    m_pDFMFare = new QDetailFormModel();
    m_pDFGrants = new QDetailFormModel(DEF_FORM_MODEL_LEE);
    m_pDFMFood = new QDetailFormModel(DEF_FORM_MODEL_LEE);
    m_pDFMTransportation = new QDetailFormModel(DEF_FORM_MODEL_LEE);
    m_pDFMUnAccommodation = new QDetailFormModel();
    m_pDFMAccommodation = new QDetailFormModel();
    m_pDFMIncidental = new QDetailFormModel();
    m_pDFMTraining = new QDetailFormModel();

    m_verpModel.append(m_pDFMTicket);
    m_verpModel.append(m_pDFMFare);
    m_verpModel.append(m_pDFGrants);
    m_verpModel.append(m_pDFMAccommodation);
    m_verpModel.append(m_pDFMIncidental);
    m_verpModel.append(m_pDFMTraining);
    m_verpModel.append(m_pDFMFood);
    m_verpModel.append(m_pDFMTransportation);
    m_verpModel.append(m_pDFMUnAccommodation);

    m_pDFMTicket->setWidgetTitle("机票：","元");
    m_pDFMFare ->setWidgetTitle("车船费：","元");
    m_pDFGrants->setWidgetTitle("出差补助：","元/天/人","天");
    m_pDFMAccommodation->setWidgetTitle("有证住宿费：","元");
    m_pDFMIncidental->setWidgetTitle("杂费：","元");
    m_pDFMTraining->setWidgetTitle("培训费：","元");
    m_pDFMFood->setWidgetTitle("伙食：","元/天/人","天");
    m_pDFMTransportation->setWidgetTitle("市内交通费：","元/天/人","天");
    m_pDFMUnAccommodation->setWidgetTitle("无证住宿补贴：","元");

    QVBoxLayout* layout = new QVBoxLayout(this);
    for (int i = 0; i < m_verpModel.count(); i++)
    {
        layout->addWidget(m_verpModel[i]);
        connect(m_verpModel[i], SIGNAL(changed()), this, SLOT(changedSlot()));
    }
    setLayout(layout);
}

double QDetailForm::getText(QString &strText)
{
    strText.clear();
    double dYuan,dTmp;
    int nCount = 0;
    QString strTmp;
    dYuan = 0;
    for(int i = 0; i < m_verpModel.count(); i++)
    {
        strTmp.clear();
        m_verpModel[i]->getText(strTmp, dTmp);
        if( dTmp == 0)
        {
            continue;
        }

        if(nCount != 0)
        {
            strText += "；\n";
        }
        strText += strTmp;
        dYuan += dTmp;
        nCount ++;
    }
    return dYuan;
}

void QDetailForm::clearText()
{
    for(int i = 0; i < m_verpModel.count(); i++)
    {
        m_verpModel[i]->clearText();
    }
}

void QDetailForm::getFormula(QString &strText)
{
    strText.clear();
    int nCount = 0;
    double dYuan = 0;
    double dRet = 0;
    QString strTmp;

    for(int i = 0; i < m_verpModel.count(); i++)
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

void QDetailForm::setDays(const int nDays)
{
    for(int i = 0; i < m_verpModel.count(); i++)
    {
        m_verpModel[i]->setDays(nDays);
    }
}

void QDetailForm::setPerCount(const int nPerCount)
{
    for(int i = 0; i < m_verpModel.count(); i++)
    {
        m_verpModel[i]->setPerCount(nPerCount);
    }
}

void QDetailForm::changedSlot()
{
    emit changed();
}

bool QDetailForm::isEmpt()
{
    for(int i = 0; i < m_verpModel.count(); i++)
    {
        if(! m_verpModel[i]->isEmpt())
        {
            return false;
        }
    }
    return true;
}
