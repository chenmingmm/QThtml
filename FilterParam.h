#pragma once
#include <string>
#include <list>

struct FilterParam
{
    FilterParam()
    {

    }

    std::string bankName;

    float Minmoney = 0.0f;

    float Maxmoney = 0.0f;

    float yearRoute = 0.0f;

    float Deductioninterestforevery100000 = 0.0f;

    int endDaysMin = 0;

    int endDaysMax = 0;

    int index = 0;
};

class CFilterParamManger
{
public:

    static CFilterParamManger * GetSingle()
    {
        static CFilterParamManger single;
        return &single;
    }

    void ReadText();
    void WriteText();

protected:
    CFilterParamManger(){}
    ~CFilterParamManger(){}



};