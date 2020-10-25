#pragma once

#include <QtWidgets/QWidget>
#include "ui_QHtml.h"
#include <x2struct.hpp>
#include <FilterParam.h>
#include <list>
#include <QNetworkAccessManager>

using namespace x2struct;

struct LoginResultData
{
    std::string accessToken;

    XTOSTRUCT(O(accessToken));
};
struct LoginResult
{
    LoginResultData data;

    XTOSTRUCT(O(data));
};

struct OrderParam
{
    std::string CHANNEL;
    std::string SOURCE;
    std::string VERSION;
    int endorseId;
    std::string hundredThousandCharge;
    int payType;
    int ticketId;
    int ticketPrice;
    int ticketType;
    bool useDefault;
    float yearRate = 0.f;
    float dealPrice = 0.f;

    XTOSTRUCT(O(ticketId, ticketType, VERSION, ticketPrice, payType, useDefault, hundredThousandCharge, endorseId, CHANNEL, SOURCE, yearRate, dealPrice));
};

struct OrderInfoParam
{
    std::string channel;
    std::string source;
    int ticketId;
    std::string version;

    XTOSTRUCT(O(channel, source, ticketId, version));
};

struct LoinInfo
{
    std::string iphone;
    std::string password;
    std::string token;
    std::string postData;
    int endorseId;
    int payType;
};

struct ReturnParam
{
    std::string code;
    std::string msg;

    XTOSTRUCT(O(code, msg));
};

struct ReturnOrderInfoParam
{
    float yearQuote = 0.f;
    float totalPrice = 0.f;
    int ticketType;
    int ticketPrice;
    int ticketId;

};

class QNetworkReply;
class QHtml : public QWidget
{
    Q_OBJECT

public:
    QHtml(QWidget *parent = Q_NULLPTR);
    ~QHtml();

    void RequestData();

    void RequestLogin();

    void RequestOrder(const struct data_list& data);

    void StartRun();

    void InitFilterParam();

    void AddFilterParam();

    void SetFilterParam();

    void SaveFilterParam();

    void InitLoginInfo();

public slots:
    void RequestFinish(QNetworkReply*);

    void RequestLoginFinish(QNetworkReply*);

    void RequestOrderFinish(QNetworkReply*);

    void DelteFilterParam();

    void ClearNetWorkManager();

private:
    Ui::QHtmlClass ui;

    LoginResult loginRes;

    LoinInfo m_loginInfo;

    std::list<FilterParam> m_filterParams;

    std::list<QNetworkAccessManager*> lstNetWorkManager;

    std::set<int> hasOrder;
};
