#pragma once

#include <QtWidgets/QWidget>
#include "ui_QHtml.h"
#include <x2struct.hpp>
#include <FilterParam.h>
#include <list>

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
    int ticketId;
    int ticketType;
    int payType;
    int endorseId;
    int ticketPrice;
    bool useDefault;
    std::string version;
    std::string hundredThousandCharge;

    XTOSTRUCT(O(ticketId, ticketType, version, ticketPrice, payType, useDefault, hundredThousandCharge, endorseId));
};

struct LoinInfo
{
    std::string iphone;
    std::string password;
    int endorseId;
    int payType;
};

struct ReturnParam
{
    std::string code;
    std::string msg;

    XTOSTRUCT(O(code, msg));
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

private:
    Ui::QHtmlClass ui;

    LoginResult loginRes;

    LoinInfo m_loginInfo;

    std::list<FilterParam> m_filterParams;
};
