#include <QCoreApplication>
#include <QtNetwork>
#include <QVariant>
#include <QMap>
#include "coin.h"
#include "jsonprocessor.h"
#include "printer.h"
#include "rawprocessor.h"

QMap<QString, QString> prepProc(QString label, QString args);
QMap<QString, QString> prepProc(QString label, QString args)
{
    QMap<QString, QString> temp;
    temp.insert(label, args);
    return temp;
}

QMap<QString, QVariant> prepare_Graviex();
QMap<QString, QVariant> prepare_StocksExchange();
QMap<QString, QVariant> prepare_Nicehash();
QMap<QString, QVariant> prepare_Tradeogre();
QMap<QString, QVariant> prepare_Cryptopia();
QMap<QString, QVariant> prepare_Octaex();
QMap<QString, QVariant> prepare_Tradesatoshi();
QMap<QString, QVariant> prepare_QBtc();
QMap<QString, QVariant> prepare_Exvo();
QMap<QString, QVariant> prepare_CryptoCompare();

void rawGo_VEGI(RawProcessor& processor, Printer& printer);
void rawGo_SOLACE(RawProcessor& processor, Printer& printer);
void rawGo_PLUS1(RawProcessor& processor, Printer& printer);
void rawGo_BTG(RawProcessor& processor, Printer& printer);
void rawGo_VRT(RawProcessor& processor, Printer& printer);
void rawGo_SONO(RawProcessor& processor, Printer& printer);
void rawGo_RVN(RawProcessor& processor, Printer& printer);
void rawGo_GRS(RawProcessor& processor, Printer& printer);
void rawGo_FTC(RawProcessor& processor, Printer& printer);
void rawGo_CREA(RawProcessor& processor, Printer& printer);
void rawGo_MSR(RawProcessor& processor, Printer& printer);
void rawGo_RTO(RawProcessor& processor, Printer& printer);
void rawGo_DERO(RawProcessor& processor, Printer& printer);
void rawGo_ETN(RawProcessor& processor, Printer& printer);
void rawGo_GRFT(RawProcessor& processor, Printer& printer);
void rawGo_XHV(RawProcessor& processor, Printer& printer);
void rawGo_IPBC(RawProcessor& processor, Printer& printer);
void rawGo_ITNS(RawProcessor& processor, Printer& printer);
void rawGo_KRB(RawProcessor& processor, Printer& printer);
void rawGo_NCP(RawProcessor& processor, Printer& printer);
void rawGo_OMB(RawProcessor& processor, Printer& printer);
void rawGo_PLURA(RawProcessor& processor, Printer& printer);
void rawGo_QWC(RawProcessor& processor, Printer& printer);
void rawGo_SPOT(RawProcessor& processor, Printer& printer);
void rawGo_XTL(RawProcessor& processor, Printer& printer);
void rawGo_TRTL(RawProcessor& processor, Printer& printer);
void rawGo_XUN(RawProcessor& processor, Printer& printer);
void rawGo_VAY(RawProcessor& processor, Printer& printer);
void rawGo_WTIP(RawProcessor& processor, Printer& printer);
void rawGo_EDL(RawProcessor& processor, Printer& printer);
void rawGo_GAME(RawProcessor& processor, Printer& printer);
void rawGo_ACH(RawProcessor& processor, Printer& printer);
void rawGo_ZLS(RawProcessor& processor, Printer& printer);
void rawGo_LTC(RawProcessor& processor, Printer& printer);
void rawGo_DASH(RawProcessor& processor, Printer& printer);
void rawGo_STRAT(RawProcessor& processor, Printer& printer);
void rawGo_BTC(RawProcessor& processor, Printer& printer);

void rawGoJson_MANI(RawProcessor& processor, Printer& printer);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Printer printer("database");

    JsonProcessor jsoner;
    QObject::connect( &jsoner, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);

/*
    jsoner.executeProcesses(prepare_Graviex());
    jsoner.executeProcesses(prepare_StocksExchange());
    jsoner.executeProcesses(prepare_Nicehash());
    jsoner.executeProcesses(prepare_Tradeogre());
    jsoner.executeProcesses(prepare_Cryptopia());
    jsoner.executeProcesses(prepare_Octaex());
    jsoner.executeProcesses(prepare_Tradesatoshi());
    jsoner.executeProcesses(prepare_QBtc());
    jsoner.executeProcesses(prepare_Exvo());
    jsoner.executeProcesses(prepare_CryptoCompare());
*/

/*
    RawProcessor rawMSR; rawGo_MSR(rawMSR, printer);
    RawProcessor rawRTO; rawGo_RTO(rawRTO, printer);
    RawProcessor rawDERO; rawGo_DERO(rawDERO, printer);
    RawProcessor rawETN; rawGo_ETN(rawETN, printer);
    RawProcessor rawGRFT; rawGo_GRFT(rawGRFT, printer);
    RawProcessor rawXHV; rawGo_XHV(rawXHV, printer);
    RawProcessor rawIPBC; rawGo_IPBC(rawIPBC, printer);
    RawProcessor rawITNS; rawGo_ITNS(rawITNS, printer);
    RawProcessor rawKRB; rawGo_KRB(rawKRB, printer);
    RawProcessor rawNCP; rawGo_NCP(rawNCP, printer);
    RawProcessor rawOMB; rawGo_OMB(rawOMB, printer);
    RawProcessor rawPLURA; rawGo_PLURA(rawPLURA, printer);
    RawProcessor rawQWC; rawGo_QWC(rawQWC, printer);
    RawProcessor rawSPOT; rawGo_SPOT(rawSPOT, printer);
    RawProcessor rawXTL; rawGo_XTL(rawXTL, printer);
    RawProcessor rawTRTL; rawGo_TRTL(rawTRTL, printer);
    RawProcessor rawXUN; rawGo_XUN(rawXUN, printer);
    RawProcessor rawVAY; rawGo_VAY(rawVAY, printer);
    RawProcessor rawWTIP; rawGo_WTIP(rawWTIP, printer);
    RawProcessor rawEDL; rawGo_EDL(rawEDL, printer);
    RawProcessor rawVEGI; rawGo_VEGI(rawVEGI, printer);
    RawProcessor rawPLUS1; rawGo_PLUS1(rawPLUS1, printer);
    RawProcessor rawBTG; rawGo_BTG(rawBTG, printer);
    RawProcessor rawRVN; rawGo_RVN(rawRVN, printer);
    //RawProcessor rawMANI; rawGoJson_MANI(rawMANI, printer);
    RawProcessor rawGRS; rawGo_GRS(rawGRS, printer);
    RawProcessor rawFTC; rawGo_FTC(rawFTC, printer);
    RawProcessor rawCREA; rawGo_CREA(rawCREA, printer);
    RawProcessor rawSOLACE; rawGo_SOLACE(rawSOLACE, printer);
    RawProcessor rawVRT; rawGo_VRT(rawVRT, printer);
    RawProcessor rawSONO; rawGo_SONO(rawSONO, printer);
    RawProcessor rawGAME; rawGo_GAME(rawGAME, printer);
    RawProcessor rawACH; rawGo_ACH(rawACH, printer);
    RawProcessor rawZLS; rawGo_ZLS(rawZLS, printer);
    RawProcessor rawLTC; rawGo_LTC(rawLTC, printer);
    RawProcessor rawDASH; rawGo_DASH(rawDASH, printer);
    RawProcessor rawSTRAT; rawGo_STRAT(rawSTRAT, printer);
*/
    RawProcessor rawBTC; rawGo_BTC(rawBTC, printer);

    return a.exec();
}
void rawGo_BTC(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "BTC"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("regex", "(\"difficulty)(.*)(,)"));
    processes.insert(index++, prepProc("regex", "[0-9]+(\\.[0-9])*"));
    processes.insert(index++, prepProc("request", "https://chain.api.btc.com/v3/block/latest"));
    processes.insert(index++, prepProc("text", "difficulty" ));
    processes.insert(index++, prepProc("regex", "(height)(.*)(,)"));
    processes.insert(index++, prepProc("regex", "[0-9]+(\\.[0-9])*"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&BTC" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_STRAT(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "STRAT"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("request", "https://chainz.cryptoid.info/strat/api.dws?q=getdifficulty"));
    processes.insert(index++, prepProc("text", "difficulty" ));
    processes.insert(index++, prepProc("request", "https://chainz.cryptoid.info/strat/api.dws?q=nethashps"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("request", "https://chainz.cryptoid.info/strat/api.dws?q=getblockcount"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&STRAT" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_DASH(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "DASH"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("request", "https://chainz.cryptoid.info/dash/api.dws?q=getdifficulty"));
    processes.insert(index++, prepProc("text", "difficulty" ));
    processes.insert(index++, prepProc("request", "https://chainz.cryptoid.info/dash/api.dws?q=nethashps"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("request", "https://chainz.cryptoid.info/dash/api.dws?q=getblockcount"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&DASH" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_LTC(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "LTC"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("request", "https://chainz.cryptoid.info/ltc/api.dws?q=getdifficulty"));
    processes.insert(index++, prepProc("text", "difficulty" ));
    processes.insert(index++, prepProc("request", "https://chainz.cryptoid.info/ltc/api.dws?q=nethashps"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("request", "https://chainz.cryptoid.info/ltc/api.dws?q=getblockcount"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&LTC" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_ZLS(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "ZLS"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("request", "http://explorer.zalias.info/api/getdifficulty"));
    processes.insert(index++, prepProc("text", "difficulty" ));
    processes.insert(index++, prepProc("request", "http://explorer.zalias.info/api/getnetworkhashps"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("request", "http://explorer.zalias.info/api/getblockcount"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&ZLS" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_ACH(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "ACH"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("request", "http://blocks.achievecoin.org/api/getdifficulty"));
    processes.insert(index++, prepProc("text", "difficulty" ));
    processes.insert(index++, prepProc("request", "http://blocks.achievecoin.org/api/getnetworkhashps"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("request", "http://blocks.achievecoin.org/api/getblockcount"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&ACH" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_GAME(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "GAME"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("regex", "(hashrate)(.*)(,)"));
    processes.insert(index++, prepProc("regex", "[0-9]+(\\.[0-9])*"));
    processes.insert(index++, prepProc("request", "https://blockexplorer.gamecredits.com/api/network/info"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("regex", "(numBlocks)(.*)(,)"));
    processes.insert(index++, prepProc("regex", "[0-9]+(\\.[0-9])*"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&GAME" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_SONO(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "SONO"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("regex", "(proof-of-work)(.*)(,)"));
    processes.insert(index++, prepProc("regex", "[0-9]+(\\.[0-9])*"));
    processes.insert(index++, prepProc("request", "https://sono.blockstats.pw/api/getdifficulty"));
    processes.insert(index++, prepProc("text", "difficulty" ));
    processes.insert(index++, prepProc("request", "https://sono.blockstats.pw/api/getnetworkhashps"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("request", "https://sono.blockstats.pw/api/getblockcount"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&SONO" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_VRT(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "VRT"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("request", "http://213.183.45.119:3001/api/getdifficulty"));
    processes.insert(index++, prepProc("text", "difficulty" ));
    processes.insert(index++, prepProc("request", "http://213.183.45.119:3001/api/getnetworkhashps"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("request", "http://213.183.45.119:3001/api/getblockcount"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&VRT" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_SOLACE(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "SOLACE"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("regex", "(Hash rate:)(.*)(s)"));
    processes.insert(index++, prepProc("regex", "[0-9]+\\.([0-9])+ .[hH]"));
    processes.insert(index++, prepProc("request", "http://explorer.solace-coin.com/"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("regex", "(Network difficulty:)(.*)(|)"));
    processes.insert(index++, prepProc("regex", "[0-9]+(\\.[0-9])*"));
    processes.insert(index++, prepProc("text", "difficulty" ));
    processes.insert(index++, prepProc("regex", "(href=./block)(.*)([0-9])+"));
    processes.insert(index++, prepProc("regex", "[0-9]+(\\.[0-9])*"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&SOLACE" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGoJson_MANI(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "MANI"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("regex", "(Hash rate:)(.*)(s)"));
    processes.insert(index++, prepProc("regex", "[0-9]+\\.([0-9])+ .[hH]"));
    processes.insert(index++, prepProc("request", "http://epicpool.net/api/currencies"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&MANI" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_CREA(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "CREA"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("request", "https://chainz.cryptoid.info/crea/api.dws?q=getdifficulty"));
    processes.insert(index++, prepProc("text", "difficulty" ));
    processes.insert(index++, prepProc("request", "https://chainz.cryptoid.info/crea/api.dws?q=nethashps"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("request", "https://chainz.cryptoid.info/crea/api.dws?q=getblockcount"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&CREA" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_EDL(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "EDL"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("regex", "(Hash rate:)(.*)(s)"));
    processes.insert(index++, prepProc("regex", "[0-9]+\\.([0-9])+ .[hH]"));
    processes.insert(index++, prepProc("request", "https://explorer.edollar.cash/"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("regex", "(Network difficulty:)(.*)(|)"));
    processes.insert(index++, prepProc("regex", "[0-9]+(\\.[0-9])*"));
    processes.insert(index++, prepProc("text", "difficulty" ));
    processes.insert(index++, prepProc("regex", "(href=./block)(.*)([0-9])+"));
    processes.insert(index++, prepProc("regex", "[0-9]+(\\.[0-9])*"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&EDL" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_WTIP(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "WTIP"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("request", "http://blockexplorer.worktips.info/q/reward/"));
    processes.insert(index++, prepProc("text", "reward" ));
    processes.insert(index++, prepProc("request", "http://blockexplorer.worktips.info/q/hashrate/"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("request", "http://blockexplorer.worktips.info/q/height/"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&WTIP" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_FTC(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "FTC"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("request", "https://chainz.cryptoid.info/ftc/api.dws?q=getdifficulty"));
    processes.insert(index++, prepProc("text", "difficulty" ));
    processes.insert(index++, prepProc("request", "https://chainz.cryptoid.info/ftc/api.dws?q=nethashps"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("request", "https://chainz.cryptoid.info/ftc/api.dws?q=getblockcount"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&FTC" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_GRS(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "GRS"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("request", "https://chainz.cryptoid.info/grs/api.dws?q=getdifficulty"));
    processes.insert(index++, prepProc("text", "difficulty" ));
    processes.insert(index++, prepProc("request", "https://chainz.cryptoid.info/grs/api.dws?q=nethashps"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("request", "https://chainz.cryptoid.info/grs/api.dws?q=getblockcount"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&GRS" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_RVN(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "RVN"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("request", "http://explorer.threeeyed.info/api/getdifficulty"));
    processes.insert(index++, prepProc("text", "difficulty" ));
    processes.insert(index++, prepProc("request", "http://explorer.threeeyed.info/api/getnetworkhashps"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("request", "http://explorer.threeeyed.info/api/getblockcount"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&RVN" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_BTG(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "BTG"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("request", "https://btgexp.com/api/getdifficulty"));
    processes.insert(index++, prepProc("text", "difficulty" ));
    processes.insert(index++, prepProc("request", "https://btgexp.com/api/getnetworkhashps"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("request", "https://btgexp.com/api/getblockcount"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&BTG" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_PLUS1(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "PLUS1"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("request", "https://blockchain.plusonecoin.org/api/getdifficulty"));
    processes.insert(index++, prepProc("text", "difficulty" ));
    processes.insert(index++, prepProc("request", "https://blockchain.plusonecoin.org/api/getnetworkhashps"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("request", "https://blockchain.plusonecoin.org/api/getblockcount"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&PLUS1" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_VEGI(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "VEGI"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("request", "http://explorer.veggiecoin.io/api/getdifficulty"));
    processes.insert(index++, prepProc("text", "difficulty" ));
    processes.insert(index++, prepProc("request", "http://explorer.veggiecoin.io/api/getnetworkhashps"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("request", "http://explorer.veggiecoin.io/api/getblockcount"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&VEGI" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_VAY(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "VAY"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("request", "http://explorer.valentinecoin.org/q/reward/"));
    processes.insert(index++, prepProc("text", "reward" ));
    processes.insert(index++, prepProc("request", "http://explorer.valentinecoin.org/q/hashrate/"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("request", "http://explorer.valentinecoin.org/q/height/"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&VAY" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_XUN(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "XUN"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("request", "http://explorer.ultranote.org/q/reward/"));
    processes.insert(index++, prepProc("text", "reward" ));
    processes.insert(index++, prepProc("request", "http://explorer.ultranote.org/q/hashrate/"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("request", "http://explorer.ultranote.org/q/height/"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&XUN" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_TRTL(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "TRTL"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("request", "https://blocks.turtle.link/q/reward/"));
    processes.insert(index++, prepProc("text", "reward" ));
    processes.insert(index++, prepProc("request", "https://blocks.turtle.link/q/hashrate/"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("request", "https://blocks.turtle.link/q/height/"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&TRTL" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_XTL(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "XTL"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("regex", "(Hash rate:)(.*)(s)"));
    processes.insert(index++, prepProc("regex", "[0-9]+\\.([0-9])+ .[hH]"));
    processes.insert(index++, prepProc("request", "https://explorer.stellite.cash/"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("regex", "(Network difficulty:)(.*)(|)"));
    processes.insert(index++, prepProc("regex", "[0-9]+(\\.[0-9])*"));
    processes.insert(index++, prepProc("text", "difficulty" ));
    processes.insert(index++, prepProc("regex", "(href=./block)(.*)([0-9])+"));
    processes.insert(index++, prepProc("regex", "[0-9]+(\\.[0-9])*"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&XTL" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_SPOT(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "SPOT"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("request", "http://explorer.spotmecoin.com/q/reward/"));
    processes.insert(index++, prepProc("text", "reward" ));
    processes.insert(index++, prepProc("request", "http://explorer.spotmecoin.com/q/hashrate/"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("request", "http://explorer.spotmecoin.com/q/height/"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&SPOT" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_QWC(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "QWC"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("request", "http://explorer.qwertycoin.org/q/reward/"));
    processes.insert(index++, prepProc("text", "reward" ));
    processes.insert(index++, prepProc("request", "http://explorer.qwertycoin.org/q/hashrate/"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("request", "http://explorer.qwertycoin.org/q/height/"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&QWC" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_PLURA(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "PLURA"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("request", "https://explorer.pluracoin.org/q/reward/"));
    processes.insert(index++, prepProc("text", "reward" ));
    processes.insert(index++, prepProc("request", "https://explorer.pluracoin.org/q/hashrate/"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("request", "https://explorer.pluracoin.org/q/height/"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&PLURA" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_OMB(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "OMB"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("regex", "(Hash rate:)(.*)(s)"));
    processes.insert(index++, prepProc("regex", "[0-9]+\\.([0-9])+ .[hH]"));
    processes.insert(index++, prepProc("request", "https://explorer.ombre.io/"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("regex", "(Network difficulty:)(.*)(|)"));
    processes.insert(index++, prepProc("regex", "[0-9]+(\\.[0-9])*"));
    processes.insert(index++, prepProc("text", "difficulty" ));
    processes.insert(index++, prepProc("regex", "(href=./block)(.*)([0-9])+"));
    processes.insert(index++, prepProc("regex", "[0-9]+(\\.[0-9])*"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&OMB" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_NCP(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "NCP"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("request", "http://www.ncpexplorer.tk/q/reward/"));
    processes.insert(index++, prepProc("text", "reward" ));
    processes.insert(index++, prepProc("request", "http://www.ncpexplorer.tk/q/hashrate/"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("request", "http://www.ncpexplorer.tk/q/height/"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&NCP" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_KRB(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "KRB"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("request", "http://explorer.karbowanec.com/q/reward/"));
    processes.insert(index++, prepProc("text", "reward" ));
    processes.insert(index++, prepProc("request", "http://explorer.karbowanec.com/q/hashrate/"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("request", "http://explorer.karbowanec.com/q/height/"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&KRB" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_ITNS(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "ITNS"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("regex", "(Hash rate:)(.*)(s)"));
    processes.insert(index++, prepProc("regex", "[0-9]+\\.([0-9])+ .[hH]"));
    processes.insert(index++, prepProc("request", "http://intensecoin.com:8081/"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("regex", "(Network difficulty:)(.*)(|)"));
    processes.insert(index++, prepProc("regex", "[0-9]+(\\.[0-9])*"));
    processes.insert(index++, prepProc("text", "difficulty" ));
    processes.insert(index++, prepProc("regex", "(href=./block)(.*)([0-9])+"));
    processes.insert(index++, prepProc("regex", "[0-9]+(\\.[0-9])*"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&ITNS" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_IPBC(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "IPBC"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("request", "https://explorer.ipbc.io/q/reward/"));
    processes.insert(index++, prepProc("text", "reward" ));
    processes.insert(index++, prepProc("request", "https://explorer.ipbc.io/q/hashrate/"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("request", "https://explorer.ipbc.io/q/height/"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&IPBC" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_XHV(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "XHV"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("regex", "(Hash rate:)(.*)(s)"));
    processes.insert(index++, prepProc("regex", "[0-9]+\\.([0-9])+ .[hH]"));
    processes.insert(index++, prepProc("request", "https://explorer.havenprotocol.com/"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("regex", "(Network difficulty:)(.*)(|)"));
    processes.insert(index++, prepProc("regex", "[0-9]+(\\.[0-9])*"));
    processes.insert(index++, prepProc("text", "difficulty" ));
    processes.insert(index++, prepProc("regex", "(href=./block)(.*)([0-9])+"));
    processes.insert(index++, prepProc("regex", "[0-9]+(\\.[0-9])*"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&XHV" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_GRFT(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "GRFT"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("regex", "(Hash rate:)(.*)(s)"));
    processes.insert(index++, prepProc("regex", "[0-9]+\\.([0-9])+ .[hH]"));
    processes.insert(index++, prepProc("request", "https://blockexplorer.graft.network/"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("regex", "(Network difficulty:)(.*)(|)"));
    processes.insert(index++, prepProc("regex", "[0-9]+(\\.[0-9])*"));
    processes.insert(index++, prepProc("text", "difficulty" ));
    processes.insert(index++, prepProc("regex", "(href=./block)(.*)([0-9])+"));
    processes.insert(index++, prepProc("regex", "[0-9]+(\\.[0-9])*"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&GRFT" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_ETN(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "ETN"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("regex", "(Hash rate:)(.*)(s)"));
    processes.insert(index++, prepProc("regex", "[0-9]+\\.([0-9])+ .[hH]"));
    processes.insert(index++, prepProc("request", "https://blockexplorer.electroneum.com/"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("regex", "(Network difficulty:)(.*)(|)"));
    processes.insert(index++, prepProc("regex", "[0-9]+(\\.[0-9])*"));
    processes.insert(index++, prepProc("text", "difficulty" ));
    processes.insert(index++, prepProc("regex", "(href=./block)(.*)([0-9])+"));
    processes.insert(index++, prepProc("regex", "[0-9]+(\\.[0-9])*"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&ETN" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_DERO(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "DERO"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("regex", "(Hash rate:)(.*)(s)"));
    processes.insert(index++, prepProc("regex", "[0-9]+\\.([0-9])+ .[hH]"));
    processes.insert(index++, prepProc("request", "https://explorer.dero.io/"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("regex", "(Network difficulty:)(.*)(|)"));
    processes.insert(index++, prepProc("regex", "[0-9]+(\\.[0-9])*"));
    processes.insert(index++, prepProc("text", "difficulty" ));
    processes.insert(index++, prepProc("regex", "(href=./block)(.*)([0-9])+"));
    processes.insert(index++, prepProc("regex", "[0-9]+(\\.[0-9])*"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&DERO" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_MSR(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "MSR"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("regex", "(Hash rate:)(.*)(s)"));
    processes.insert(index++, prepProc("regex", "[0-9]+\\.([0-9])+ .[hH]"));
    processes.insert(index++, prepProc("request", "https://msrchain.net/"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("regex", "(Network difficulty:)(.*)(|)"));
    processes.insert(index++, prepProc("regex", "[0-9]+(\\.[0-9])*"));
    processes.insert(index++, prepProc("text", "difficulty" ));
    processes.insert(index++, prepProc("regex", "(href=./block)(.*)([0-9])+"));
    processes.insert(index++, prepProc("regex", "[0-9]+(\\.[0-9])*"));
    processes.insert(index++, prepProc("text", "height" ));
    //processes.insert(9, prepProc("regex", "(Server time:)(.*)(|)"));
    //processes.insert(10, prepProc("regex", "([0-9])+-([0-9])+-([0-9])+( )+([0-9])+:([0-9])+:([0-9])+"));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&MSR" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
void rawGo_RTO(RawProcessor& processor, Printer& printer)
{
    QObject::connect( &processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             &printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
    QList< QMap<QString, QString> > processes;
    int index = 0;
    //editable
    processes.insert(index++, prepProc("name", "RTO"));
    processes.insert(index++, prepProc("type", "mining"));
    processes.insert(index++, prepProc("request", "http://explorer.arto.cash/q/reward/"));
    processes.insert(index++, prepProc("text", "reward" ));
    processes.insert(index++, prepProc("request", "http://explorer.arto.cash/q/hashrate/"));
    processes.insert(index++, prepProc("text", "hashrate" ));
    processes.insert(index++, prepProc("request", "http://explorer.arto.cash/q/height/"));
    processes.insert(index++, prepProc("text", "height" ));
    processes.insert(index++, prepProc("now", "timedate" ));
    processes.insert(index++, prepProc("reference", "symbol&RTO" ));
    processes.insert(index++, prepProc("result", ""));
    //end of editable
    processor.executeProcesses(processes);
}
QMap<QString, QVariant> prepare_CryptoCompare()
{
    QMap<QString, QVariant> processes;
    processes.insert( "0#name", "CryptoCompare");
    processes.insert( "1#type", "coinsdata");
    processes.insert( "2#pretickers", "https://www.cryptocompare.com/api/data/coinlist/");
    processes.insert( "3#functiononly", "valargs(Data|non),"
    "doctovariant(),objlist(symbol|non|Symbol&symbol|CoinName&coin_name|Algorithm&algorithm|ProofType&proof|FullyPremined&premined"
    "|TotalCoinSupply&supply),append()" );
    processes.insert( "4#result", "");
    return processes;
}
QMap<QString, QVariant> prepare_Exvo()
{
    QMap<QString, QVariant> processes;
    processes.insert( "0#name", "Exvo");
    processes.insert( "1#type", "exchange");
    processes.insert( "2#pretickers", "https://exvo.io/api/v2/markets.json");
    processes.insert( "3#markets", "https://exvo.io/api/v2/tickers.json");
    processes.insert( "4#marketsfunction", "array(),variantlist(name&pairName|id&pairId)" );
    processes.insert( "5#functiononly", "non(),mergebyreferencedocwithpreparameter(pairId|ticker|last&last|high&high|low&low|vol&vol|buy&buy|sell&sell)" );
    processes.insert( "6#result", "");
    return processes;
}
QMap<QString, QVariant> prepare_QBtc()
{
    QMap<QString, QVariant> processes;
    processes.insert( "0#name", "QBTC");
    processes.insert( "1#type", "exchange");
    processes.insert( "2#pretickers", "https://www.qbtc.com/json/getAllCoinInfo.do");
    processes.insert( "3#functiononly", "valargs(result|non),valarray(),"
    "variantlist(symbol&pairName|high&high|low&low|volume&vol|buyone&buy|sellone&sell|last&last),append()" );
    processes.insert( "4#result", "");
    return processes;
}
QMap<QString, QVariant> prepare_Tradesatoshi()
{
    QMap<QString, QVariant> processes;
    processes.insert( "0#name", "TRADESATOSHI");
    processes.insert( "1#type", "exchange");
    processes.insert( "2#pretickers", "https://tradesatoshi.com/api/public/getmarketsummaries");
    processes.insert( "3#functiononly", "valargs(result|non),valarray(),"
    "variantlist(market&pairName|high&high|low&low|volume&vol|bid&buy|ask&sell|last&last|change&change),append()" );
    processes.insert( "4#result", "");
    return processes;
}
QMap<QString, QVariant> prepare_Octaex()
{
    QMap<QString, QVariant> processes;
    processes.insert( "0#name", "Octaex");
    processes.insert( "1#type", "exchange");
    processes.insert( "2#pretickers", "https://www.octaex.com/api/trade/all/");
    processes.insert( "3#functiononly", "objlist(pairName|non|new_price&price|max_price&high|min_price&low|amount&vol|buy_price&buy|sell_price&sell),append()" );
    processes.insert( "4#result", "");
    return processes;
}
QMap<QString, QVariant> prepare_Cryptopia()
{
    QMap<QString, QVariant> processes;
    processes.insert( "0#name", "Cryptopia");
    processes.insert( "1#type", "exchange");
    processes.insert( "2#pretickers", "https://www.cryptopia.co.nz/api/GetMarkets");
    processes.insert( "3#functiononly", "valargs(Data|non),valarray(),"
    "variantlist(Label&pairName|High&high|Low&low|Volume&vol|BidPrice&buy|AskPrice&sell|LastPrice&last|Change&change|TradePairId&pairId),append()" );
    processes.insert( "4#result", "");
    return processes;
}
QMap<QString, QVariant> prepare_Tradeogre()
{
    QMap<QString, QVariant> processes;
    processes.insert( "0#name", "Tradeogre");
    processes.insert( "1#type", "exchangeinverted");
    processes.insert( "2#pretickers", "https://tradeogre.com/api/v1/markets");
    processes.insert( "3#functiononly", "array(),mapobjlist(pairName|price&price|high&high|low&low|volume&vol|bid&buy|ask&sell),append()" );
    processes.insert( "4#result", "");
    return processes;
}
QMap<QString, QVariant> prepare_Nicehash()
{
    QMap<QString, QVariant> processes;
    processes.insert( "0#name", "Nicehash");
    processes.insert( "1#type", "hash");
    processes.insert( "2#pretickers", "https://api.nicehash.com/api?method=buy.info");
    processes.insert( "3#markets", "https://api.nicehash.com/api?method=stats.global.current");
    processes.insert( "4#marketsfunction", "valargs(result|algorithms),valarray(),"
    "variantlist(algo&id|name&name|min_diff_initial&diff|speed_text&unit|min_limit&limit|"
    "min_diff_initial&initial_minimum_diff|min_diff_working&working_minimum_diff)" );
    processes.insert( "5#functiononly", "non(),valargs(result|stats),"
    "valarray(),variantlistmerge(algo|id|price&price)" );
    processes.insert( "6#result", "");
    return processes;
}
QMap<QString, QVariant> prepare_Graviex()
{
    QMap<QString, QVariant> processes;
    processes.insert( "0#name", "Graviex");
    processes.insert( "1#type", "exchange");
    processes.insert( "2#pretickers", "https://graviex.net:443//api/v2/markets.json");
    processes.insert( "3#markets", "https://graviex.net:443//api/v2/tickers.json");
    processes.insert( "4#marketsfunction", "array(),variantlist(name&pairName|id&pairId)" );
    processes.insert( "5#functiononly", "non(),mergebyreferencedocwithpreparameter"
    "(pairId|ticker|buy&buy|sell&sell|low&low|high&high|last&last|vol&vol|volbtc&volbtc|change&change)" );
    processes.insert( "6#result", "");
    return processes;
}
QMap<QString, QVariant> prepare_StocksExchange()
{
    QMap<QString, QVariant> processes;
    processes.insert( "0#name", "Stocks.Exchange");
    processes.insert( "1#type", "exchange");
    processes.insert( "2#pretickers", "https://stocks.exchange/api2/markets");
    processes.insert( "3#markets", "https://stocks.exchange/api2/ticker");
    processes.insert( "4#marketsfunction", "array(),variantlist(market_name&pairName)" );
    processes.insert( "5#functiononly", "array(),variantlistmerge"
    "(market_name|pairName|last&last|vol&vol|ask&sell|bid&buy)" );
    processes.insert( "6#result", "");
    return processes;
}
