#pragma once

#include<QThread>
#include <QMutex>
#include<string>

class QRequestThread :public QThread
{
    Q_OBJECT

public:

    static QRequestThread*Get()
    {
        static QRequestThread vt;
        return &vt;
    }

    virtual void run()override;


signals:
    void RequestDataFinishSignals();

public:

    bool bStart = false;

    int timeInterval = 1000;

private:
    QRequestThread();
    ~QRequestThread();

    QMutex mutex;
    

};

