#ifndef APP_H
#define APP_H

#include <QObject>
#include <QTime>
#include <QtNetwork>
#include <QVariant>
#include <QMap>
#include "jsonprocessor.h"
#include "printer.h"
#include "rawprocessor.h"

class App : public QObject
{
    Q_OBJECT
private:
    QTimer* timer;
    QChar option;

    JsonProcessor jsoner;
    Printer* printer;

    static QList< QMap<QString, QVariant> (*) (void)> jsonOldProcesses;
    static int jsonOldCount;
    int jsonOldIndex;

    static QList< QList< QMap<QString, QString> > > rawProcesses;
    static QList< RawProcessor* > rawProcessesToDelete;
    static int rawCount;
    int rawIndex;

    int totalIndex;
    int totalCount;
public:
    explicit App(QObject *parent = nullptr);
    ~App() { delete printer; for(int i=0;i<rawProcessesToDelete.size();i++) delete rawProcessesToDelete[i]; delete timer; }
signals:
    void finished();

public slots:
    void run();
    void end();

    void timeUp();
private:
    static QMap<QString, QString> prepProc(QString label, QString args);
    static void add_jsonOldProcesses(QMap<QString, QVariant>(*arg)(void));
    void execute_jsonOldProcesses();

    static void add_rawProcesses(QList< QMap<QString, QString> >(*arg)(void));
    void execute_rawProcesses();

    static QMap<QString, QVariant> prepare_WhatToMine();

    static QMap<QString, QVariant> prepare_Graviex();
    static QMap<QString, QVariant> prepare_StocksExchange();
    static QMap<QString, QVariant> prepare_Nicehash();
    static QMap<QString, QVariant> prepare_Tradeogre();
    static QMap<QString, QVariant> prepare_Cryptopia();
    static QMap<QString, QVariant> prepare_Octaex();
    static QMap<QString, QVariant> prepare_Tradesatoshi();
    static QMap<QString, QVariant> prepare_QBtc();
    static QMap<QString, QVariant> prepare_Exvo();
    static QMap<QString, QVariant> prepare_CryptoCompare();
    static QMap<QString, QVariant> prepare_Crex24();
    static QMap<QString, QVariant> prepare_Altex();

    static QList< QMap<QString, QString> > rawGoJson_MANI();

    static QList< QMap<QString, QString> > rawGo_ZEC();
    static QList< QMap<QString, QString> > rawGo_VEGI();
    static QList< QMap<QString, QString> > rawGo_SOLACE();
    static QList< QMap<QString, QString> > rawGo_PLUS1();
    static QList< QMap<QString, QString> > rawGo_BTG();
    static QList< QMap<QString, QString> > rawGo_VRT();
    static QList< QMap<QString, QString> > rawGo_SONO();
    static QList< QMap<QString, QString> > rawGo_RVN();
    static QList< QMap<QString, QString> > rawGo_GRS();
    static QList< QMap<QString, QString> > rawGo_FTC();
    static QList< QMap<QString, QString> > rawGo_CREA();
    static QList< QMap<QString, QString> > rawGo_MSR();
    static QList< QMap<QString, QString> > rawGo_RTO();
    static QList< QMap<QString, QString> > rawGo_DERO();
    static QList< QMap<QString, QString> > rawGo_ETN();
    static QList< QMap<QString, QString> > rawGo_GRFT();
    static QList< QMap<QString, QString> > rawGo_XHV();
    static QList< QMap<QString, QString> > rawGo_IPBC();
    static QList< QMap<QString, QString> > rawGo_ITNS();
    static QList< QMap<QString, QString> > rawGo_KRB();
    static QList< QMap<QString, QString> > rawGo_NCP();
    static QList< QMap<QString, QString> > rawGo_OMB();
    static QList< QMap<QString, QString> > rawGo_PLURA();
    static QList< QMap<QString, QString> > rawGo_QWC();
    static QList< QMap<QString, QString> > rawGo_SPOT();
    static QList< QMap<QString, QString> > rawGo_XTL();
    static QList< QMap<QString, QString> > rawGo_TRTL();
    static QList< QMap<QString, QString> > rawGo_XUN();
    static QList< QMap<QString, QString> > rawGo_VAY();
    static QList< QMap<QString, QString> > rawGo_WTIP();
    static QList< QMap<QString, QString> > rawGo_EDL();
    static QList< QMap<QString, QString> > rawGo_GAME();
    static QList< QMap<QString, QString> > rawGo_ACH();
    static QList< QMap<QString, QString> > rawGo_ZLS();
    static QList< QMap<QString, QString> > rawGo_LTC();
    static QList< QMap<QString, QString> > rawGo_DASH();
    static QList< QMap<QString, QString> > rawGo_STRAT();
    static QList< QMap<QString, QString> > rawGo_BTC();
};

#endif // APP_H
