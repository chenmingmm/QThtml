#include "QHtml.h"
#include <qnetworkrequest.h>
#include<QNetworkReply>
#include <QDebug>
#include <iostream>
#include <QTextCodec>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QTableWidget>
#include <list>
#include <QRequestThread.h>
#include <qpushbutton.h>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QDateTime>
#include <QTextEdit>
#include <iostream>
#include <QMessageBox>  
#include <QSettings>  //读写ini文件

enum RETURNCODE
{
    RETURNCODE_BANKNAME = 1,
    RETURNCODE_FLAW,
    RETURNCODE_YEARROUTE,
    RETURNCODE_DATA,
    RETURNCODE_MONEY,

    RETURNCODE_SUCCESS
};


struct data_list
{
    float ticketPrice = 0.0f;  // 金额
    float yearQuote = 0.0f;//年息
    std::string endTime; // 到期日
    std::string bankName;
    std::string sellPrice; //每十万扣息
    std::string tradeEndorseTime;
    std::string flawDescription; //瑕疵
    int ticketId;
    int ticketType;
    int rateDay;

    int IsDataMeetParam(const FilterParam& param)
    {
        if (std::string::npos == bankName.find(param.bankName) && !param.bankName.empty()) {
            return RETURNCODE_BANKNAME;
        }

        QString str = QString::fromLocal8Bit("无瑕疵");
        if (flawDescription != str.toStdString()) {
            return RETURNCODE_FLAW;
        }

        std::string _endTime;
        std::string year = "20";
        _endTime = year + endTime;
        QDateTime time;
        time = QDateTime::fromString(_endTime.c_str(), "yyyy.MM.dd");
        QDateTime curtime = QDateTime::currentDateTime();
        qint64 intervalTime = curtime.secsTo(time);
        int day = intervalTime / (3600 * 24) + 1;

        if (day < param.endDaysMin && param.endDaysMin != 0) {
            return RETURNCODE_DATA;
        }

        if (day > param.endDaysMax && param.endDaysMax != 0) {
            return RETURNCODE_DATA;
        }

        if ((ticketPrice < param.Minmoney && !qFuzzyIsNull(param.Minmoney))|| (ticketPrice > param.Maxmoney && !qFuzzyIsNull(param.Maxmoney))) {
            return RETURNCODE_MONEY;
        }

        int tenNum = (int)ticketPrice / 10;
        if (!qFuzzyIsNull(param.yearRoute)) {
            float price = (ticketPrice * 10000.f * (param.yearRoute * 0.01f) * rateDay) / 360.f + (param.Deductioninterestforevery100000 * tenNum);
            if (price >= atof(sellPrice.c_str()) * tenNum) {
                return RETURNCODE_YEARROUTE;
            }
        }

        return RETURNCODE_SUCCESS;
    }
  

    XTOSTRUCT(O(yearQuote, endTime, bankName, sellPrice, ticketPrice, tradeEndorseTime, flawDescription, ticketId, ticketType, rateDay));
};

struct Showdata
{
    std::list<data_list> list;

    XTOSTRUCT(O(list));
};

struct InputParam 
{
    std::string code;
    Showdata data;
    std::string msg;

    XTOSTRUCT(O(code, data, msg));
};

struct LoginParam
{
    std::string password;
    std::string phone;
    std::string version;

    XTOSTRUCT(O(password, phone, version));
};


QHtml::QHtml(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    setWindowTitle(QString::fromLocal8Bit("抢票"));
    ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    InitFilterParam();
    InitLoginInfo();
   
    QObject::connect(ui.startbutton, &QPushButton::clicked, this, &QHtml::StartRun);
    QObject::connect(ui.addFilterParamBtn, &QPushButton::clicked, this, &QHtml::AddFilterParam);
    QObject::connect(ui.setFilterParamBtn, &QPushButton::clicked, this, &QHtml::SetFilterParam);
    RequestLogin();
   
}

QHtml::~QHtml()
{
    SaveFilterParam();
}

void QHtml::RequestData()
{
    QNetworkAccessManager* naManager = new QNetworkAccessManager;
    QNetworkRequest request;
    request.setUrl(QUrl("https://new.tcpjw.com/order-web/orderInfo/getTradingOrderInfo"));
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.169 Safari/537.36");
    request.setRawHeader("Cookie", "acw_tc=74cf71a215737323978855511e5b80da827895d64081a603db520fd2c8; access_token=9c1b635e-8101-4f8c-8e7d-659324f9d201");
    request.setRawHeader("Content-Type", "application/json;charset=UTF-8");
    std::string authorization = "Bearer " + loginRes.data.accessToken;
    request.setRawHeader("Authorization", authorization.c_str());
    request.setRawHeader("Content-Length", "381");
    request.setRawHeader("Accept-Language", "zh-CN,zh;q=0.9");
    //request.setRawHeader("Accept-Encoding", "gzip, deflate, br");
    QByteArray postData;
    postData.append("{\"version\":\"3.5\",\"channel\":\"01\",\"pageNum\":1,\"pageSize\":30}");
    naManager->post(request, postData);

    QObject::connect(naManager, &QNetworkAccessManager::finished, this, &QHtml::RequestFinish);
    lstNetWorkManager.push_back(naManager);
}

void QHtml::RequestLogin()
{
    QNetworkAccessManager* naManager = new QNetworkAccessManager;
    QNetworkRequest request;
    request.setUrl(QUrl("https://www.tcpjw.com/commodule-web/account/login"));
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.169 Safari/537.36");
    request.setRawHeader("Content-Type", "application/json");
    QByteArray postData;
    LoginParam param;

    param.phone = m_loginInfo.iphone;
    param.password = m_loginInfo.password;
    param.version = "3.5";
    std::string paramstr = X::tojson(param);
    postData.append(paramstr.c_str());
    naManager->post(request, postData);

    QObject::connect(naManager, &QNetworkAccessManager::finished, this, &QHtml::RequestLoginFinish);
    lstNetWorkManager.push_back(naManager);
}

void QHtml::RequestOrder(const data_list& data)
{
    QNetworkAccessManager* naManager = new QNetworkAccessManager;
    QNetworkRequest request;
    request.setUrl(QUrl("https://www.tcpjw.com/order-web/orderFlow/quoteOrder"));
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.169 Safari/537.36");
    std::string authorization = "Bearer " + loginRes.data.accessToken;
    request.setRawHeader("Authorization", authorization.c_str());
    request.setRawHeader("Content-Type", "application/json");

    QByteArray postData;
    OrderParam param;
    param.ticketId = data.ticketId;
    param.VERSION = "3.5";
    param.useDefault = false;
    param.ticketPrice = (int)data.ticketPrice;
    param.ticketType = data.ticketType;
    param.payType = m_loginInfo.payType;
    param.endorseId = m_loginInfo.endorseId;
    param.hundredThousandCharge = data.sellPrice;
    param.yearRate = data.yearQuote;
    param.dealPrice = data.ticketPrice - (data.ticketPrice * data.yearQuote * 100 * data.rateDay) / 360 / 10000;
    param.CHANNEL = "01";
    param.SOURCE = "HTML";
    std::string paramstr = X::tojson(param);

    char buff[1024] = {0};
    QString yearRate = QString::number(data.yearQuote);
    QString dealPrice = QString::number(param.dealPrice);
    QString poststring = QString("{\"ticketId\":%1,\"ticketType\":%2,\"VERSION\":\"3.5\",\"ticketPrice\":%3,\"payType\":%4,\"useDefault\":false,\"hundredThousandCharge\":\"%5\",\"endorseId\":%6,\"CHANNEL\":\"01\",\"SOURCE\":\"HTML\",\"yearRate\":%7,\"dealPrice\":%8}").
        arg(data.ticketId).arg(data.ticketType).arg(data.ticketPrice).arg(m_loginInfo.payType).arg(data.sellPrice.c_str()).arg(m_loginInfo.endorseId).arg(yearRate).arg(dealPrice);
    postData.append(poststring);
    naManager->post(request, postData);
    QObject::connect(naManager, &QNetworkAccessManager::finished, this, &QHtml::RequestOrderFinish);
}

void QHtml::StartRun()
{
    QRequestThread::Get()->bStart = !QRequestThread::Get()->bStart;
    ui.tableWidget->setRowCount(0);

    if (QRequestThread::Get()->bStart) {
        ui.startbutton->setText(QString::fromLocal8Bit("停止"));
    }
    else {
        ui.startbutton->setText(QString::fromLocal8Bit("开始"));
    }
} 

void QHtml::InitFilterParam()
{
    std::ifstream ifs("filter_param.txt");
    if (!ifs.is_open()) {
        return;
    }
    QString str;
    QStringList list;
    std::string tempStr;
    int index = 0;
    while (getline(ifs, tempStr))
    {
        str = tempStr.c_str();
        if (str.isEmpty() || str.contains(QString::fromLocal8Bit("金额")))
        {
            continue;
        }
        list = str.split('\t');
        if (list.size() < 7) {
            continue;
        }
        FilterParam param;
        param.bankName = list.at(0).toStdString();
        param.Minmoney = list.at(1).toDouble();
        param.Maxmoney = list.at(2).toDouble();
        param.yearRoute = list.at(3).toDouble();
        param.Deductioninterestforevery100000 = list.at(4).toDouble();
        param.endDaysMin = list.at(5).toInt();
        param.endDaysMax = list.at(6).toInt();
        param.index = index;
        index++;
        m_filterParams.push_back(param);
    }

    for (const auto& filter : m_filterParams) {
        ui.filterList->insertRow(filter.index);
        QLineEdit *le1 = new QLineEdit();
        le1->setText(filter.bankName.c_str());
        QDoubleSpinBox *sb = new QDoubleSpinBox();
        sb->setRange(0, 999);
        sb->setValue(filter.Minmoney);
        QDoubleSpinBox *sb1 = new QDoubleSpinBox();
        sb1->setRange(0, 999);
        sb1->setValue(filter.Maxmoney);
        QDoubleSpinBox *sb2 = new QDoubleSpinBox();
        sb2->setRange(0, 9999);
        sb2->setValue(filter.yearRoute);
        QDoubleSpinBox *sb3 = new QDoubleSpinBox();
        sb3->setRange(0, 999);
        sb3->setValue(filter.Deductioninterestforevery100000);
        QSpinBox *sb4 = new QSpinBox();
        sb4->setRange(0, 999);
        sb4->setValue(filter.endDaysMin);
        QSpinBox *sb5 = new QSpinBox();
        sb5->setRange(0, 999);
        sb5->setValue(filter.endDaysMax);
        ui.filterList->setCellWidget(filter.index, 0, le1);
        ui.filterList->setCellWidget(filter.index, 1, sb);
        ui.filterList->setCellWidget(filter.index, 2, sb1);
        ui.filterList->setCellWidget(filter.index, 3, sb2);
        ui.filterList->setCellWidget(filter.index, 4, sb3);
        ui.filterList->setCellWidget(filter.index, 5, sb4);
        ui.filterList->setCellWidget(filter.index, 6, sb5);
    }
}

void QHtml::AddFilterParam()
{
    int row = ui.filterList->rowCount();
    ui.filterList->insertRow(row);
    QLineEdit *le1 = new QLineEdit();
    le1->setText("");
    QDoubleSpinBox *sb = new QDoubleSpinBox();
    sb->setRange(0, 999);
    QDoubleSpinBox *sb1 = new QDoubleSpinBox();
    sb1->setRange(0, 999);
    QDoubleSpinBox *sb2 = new QDoubleSpinBox();
    sb2->setRange(0, 9999);
    QDoubleSpinBox *sb3 = new QDoubleSpinBox();
    sb3->setRange(0, 999);
    QSpinBox *sb4 = new QSpinBox();
    sb4->setRange(0, 999);
    QSpinBox *sb5 = new QSpinBox();
    sb5->setRange(0, 999);
    ui.filterList->setCellWidget(row, 0, le1);
    ui.filterList->setCellWidget(row, 1, sb);
    ui.filterList->setCellWidget(row, 2, sb1);
    ui.filterList->setCellWidget(row, 3, sb2);
    ui.filterList->setCellWidget(row, 4, sb3);
    ui.filterList->setCellWidget(row, 5, sb4);
    ui.filterList->setCellWidget(row, 6, sb5);
}

void QHtml::SetFilterParam()
{
    m_filterParams.clear();
    for (int i = 0; i < ui.filterList->rowCount(); i++)
    {
        FilterParam param;
        auto le = (QLineEdit*)ui.filterList->cellWidget(i, 0);
        param.bankName = le->text().toStdString();

        auto sb = (QDoubleSpinBox*)ui.filterList->cellWidget(i, 1);
        param.Minmoney = sb->value();

        auto sb4 = (QDoubleSpinBox*)ui.filterList->cellWidget(i, 2);
        param.Maxmoney = sb4->value();

        auto sb1 = (QDoubleSpinBox*)ui.filterList->cellWidget(i, 3);
        param.yearRoute = sb1->value();

        auto sb2 = (QDoubleSpinBox*)ui.filterList->cellWidget(i, 4);
        param.Deductioninterestforevery100000 = sb2->value();

        auto sb3 = (QSpinBox*)ui.filterList->cellWidget(i, 5);
        param.endDaysMin = sb3->value();

        auto sb5 = (QSpinBox*)ui.filterList->cellWidget(i, 6);
        param.endDaysMax = sb5->value();
        param.index = i;
        m_filterParams.push_back(param);
    }
    QMessageBox::information(this, QString::fromLocal8Bit("设置"), QString::fromLocal8Bit("设置筛选条件成功"));
   
}

void QHtml::SaveFilterParam()
{
    std::ofstream ofs("filter_param.txt");
    if (!ofs.is_open()) {
        return;
    }
    for (const auto& filter : m_filterParams) {
        ofs << filter.bankName << '\t' << filter.Minmoney << '\t' << filter.Maxmoney << '\t' << filter.yearRoute << '\t' << filter.Deductioninterestforevery100000 << '\t' << filter.endDaysMin << '\t' << filter.endDaysMax <<"\r\n";
    }
}

void QHtml::InitLoginInfo()
{
    QSettings configIni("login.ini", QSettings::IniFormat);
    m_loginInfo.iphone = configIni.value("loginInfo/iphone").toString().toStdString();
    m_loginInfo.password = configIni.value("loginInfo/password").toString().toStdString();
    m_loginInfo.endorseId = configIni.value("loginInfo/endorseId").toInt();
    m_loginInfo.payType = configIni.value("loginInfo/payType").toInt();
    QRequestThread::Get()->timeInterval = (configIni.value("Time/timeInterval").toInt()*1000);
}

void QHtml::DelteFilterParam()
{
    int currow = ui.filterList->currentRow();
    for (auto iter = m_filterParams.begin(); iter != m_filterParams.end();) {
        if (iter->index == currow) {
            iter = m_filterParams.erase(iter);
            ui.filterList->removeRow(currow);
            QMessageBox::information(this, QString::fromLocal8Bit("删除"), QString::fromLocal8Bit("删除筛选条件成功"));
        } else {
            ++iter;
        }
    }
}

void QHtml::ClearNetWorkManager()
{
    auto iter = lstNetWorkManager.begin();
    for (; iter != lstNetWorkManager.end(); iter++)
    {
        delete *iter;
    }
    lstNetWorkManager.clear();
}

void QHtml::RequestFinish(QNetworkReply* reply)
{
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    if (statusCode.isValid())
    {
        qDebug() << "status code=" << statusCode.toInt();
    }

    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    if (reason.isValid())
        qDebug() << "reason=" << reason.toString();

    QNetworkReply::NetworkError err = reply->error();
    if (err != QNetworkReply::NoError) {
        qDebug() << "Failed: " << reply->errorString();
    }
    else {
        QByteArray read = reply->readAll();
        QString str = read.data();
        QString  readstring = QString::fromUtf8(read);

        InputParam param;
        X::loadjson(readstring.toStdString(), param, false);
        int index = 0;
        ui.tableWidget->clearContents();
        ui.tableWidget->setRowCount(param.data.list.size());
        bool filter = true;
        int ret = 0;
        int meetCount = 0;
        for (auto iter : param.data.list)
        {
            for (const auto& filterIter : m_filterParams)
            {
                filter = false;
                if (hasOrder.end() != hasOrder.find(iter.ticketId)) {
                    break;
                }
                ret = iter.IsDataMeetParam(filterIter);
                if (ret == RETURNCODE_SUCCESS) {
                    filter = true;
                    ui.LogOutput->append(QString::fromLocal8Bit("校验成功开始抢票"));
                    hasOrder.insert(iter.ticketId);
                    meetCount++;
                    RequestOrder(iter);
                    break;
                }
            }
            if (filter) {
                ui.tableWidget->setItem(index, 0, new QTableWidgetItem(iter.bankName.c_str()));
                int tickprice = iter.ticketPrice;
                ui.tableWidget->setItem(index, 1, new QTableWidgetItem(QString("%1").arg(tickprice)));//金额
                ui.tableWidget->setItem(index, 2, new QTableWidgetItem(iter.endTime.c_str()));//到期日
                ui.tableWidget->setItem(index, 3, new QTableWidgetItem(iter.sellPrice.c_str()));//每十万扣息
                ui.tableWidget->setItem(index, 4, new QTableWidgetItem(QString("%1").arg(iter.yearQuote)));//年息
                ui.tableWidget->setItem(index, 5, new QTableWidgetItem(iter.flawDescription.c_str()));//瑕疵                      
                ui.tableWidget->setItem(index, 6, new QTableWidgetItem(iter.tradeEndorseTime.c_str()));//交易平均时长
                index++;
            }
        }
        if (meetCount == 0) {
            QTime time = QTime::currentTime();
            QString str;
            switch (ret)
            {
            case RETURNCODE_BANKNAME:          
                ui.LogOutput->append(time.toString() + QString::fromLocal8Bit(" 承兑人校验失败"));
                break;
            case RETURNCODE_FLAW:
                ui.LogOutput->append(time.toString() + QString::fromLocal8Bit(" 有无瑕疵校验失败"));
                break;
            case RETURNCODE_YEARROUTE:
                ui.LogOutput->append(time.toString() + QString::fromLocal8Bit(" 年息校验失败"));
                break;
            case RETURNCODE_DATA:
                ui.LogOutput->append(time.toString() + QString::fromLocal8Bit(" 剩余天数校验失败"));
                break;
            case RETURNCODE_MONEY:
                ui.LogOutput->append(time.toString() + QString::fromLocal8Bit(" 金额校验失败"));
                break;
            default:
                break;
            }
        }    
    }   

    ClearNetWorkManager();
}

void QHtml::RequestLoginFinish(QNetworkReply*reply)
{
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    if (reason.isValid())
        qDebug() << "reason=" << reason.toString();

    QNetworkReply::NetworkError err = reply->error();
    if (err != QNetworkReply::NoError) {
        qDebug() << "Failed: " << reply->errorString();
    }
    else {
        QByteArray read = reply->readAll();
        QString str = read.data();
        QString  readstring = QString::fromUtf8(read);
        X::loadjson(readstring.toStdString(), loginRes, false);
        if (!loginRes.data.accessToken.empty()) {
            QObject::connect(QRequestThread::Get(), &QRequestThread::RequestDataFinishSignals, this, &QHtml::RequestData);
            char buff[128];
            sprintf(buff, "<font color=\"#66CC00\">%s 登陆成功</font>", m_loginInfo.iphone.c_str());
            ui.LogOutput->append(QString::fromLocal8Bit(buff));
        } else {
            char buff[128];
            sprintf(buff, "<font color=\"#FF0000\">%s 登陆失败</font>", m_loginInfo.iphone.c_str());          
            ui.LogOutput->append(QString::fromLocal8Bit(buff));
        }
       
    }
}

void QHtml::RequestOrderFinish(QNetworkReply* reply)
{
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    if (statusCode.isValid())
    {
        qDebug() << "status code=" << statusCode.toInt();
    }

    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    if (reason.isValid())
        qDebug() << "reason=" << reason.toString();

    QNetworkReply::NetworkError err = reply->error();
    if (err != QNetworkReply::NoError) {
        qDebug() << "Failed: " << reply->errorString();
    }
    else {
        ReturnParam returnParam;
        QByteArray read = reply->readAll();
        QString str = read.data();
        QString  readstring = QString::fromUtf8(read);
        X::loadjson(readstring.toStdString(), returnParam, false);
        QTime time = QTime::currentTime();
        QString tempstr;
        QString spinrtStr = QString::fromLocal8Bit("<font color=\"#66CC00\">%s 抢票结果 : %s</font>");
        tempstr.sprintf(spinrtStr.toStdString().c_str(), time.toString().toStdString().c_str(), returnParam.msg.c_str());
        ui.LogOutput->append(QString::fromUtf8(tempstr.toStdString().c_str()));
    }
}
