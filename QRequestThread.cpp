#include "QRequestThread.h"
#include <qnetworkrequest.h>
#include <QNetworkAccessManager>
#include<QNetworkReply>
#include <QDebug>
#include <iostream>
#include <QTextCodec>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QTableWidget>
#include <windows.h>


void QRequestThread::run()
{
    while (true)
    {
        mutex.lock();
        if (bStart)
        {
            RequestDataFinishSignals();
            mutex.unlock();
            Sleep(timeInterval);
            continue;
        }
        mutex.unlock();
        
    }
    
}

QRequestThread::QRequestThread()
{
    start();
}

QRequestThread::~QRequestThread()
{
    wait();
    quit();
}
