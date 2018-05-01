#include "app.h"
#include <QTextStream>
#include <QDebug>

int App::jsonOldCount = 0;
QList< QMap<QString, QVariant> (*) (void)> App::jsonOldProcesses;

QList< QList< QMap<QString, QString> > > App::rawProcesses;
QList< RawProcessor* > App::rawProcessesToDelete;
int App::rawCount = 0;

App::App(QObject *parent) : QObject(parent)
{
    totalIndex = 0;
    totalCount = 0;

    printer = new Printer("database");

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeUp()));

    QObject::connect( &jsoner, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
             printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);

    QObject::connect( printer, SIGNAL(pleaseEnd()), this, SLOT(end()), Qt::QueuedConnection);
}
void App::timeUp()
{
    if(totalIndex < jsonOldCount)
    {
        printer->addObjectCounts(1);
        jsoner.executeProcesses((*jsonOldProcesses[totalIndex])());
    }else
    {
        int indexShiftedOldJson = totalIndex - jsonOldCount;
        printer->addObjectCounts(1);
        RawProcessor* processor = new RawProcessor();
        QObject::connect( processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
                 printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
        processor->executeProcesses(rawProcesses[indexShiftedOldJson]);
        rawProcessesToDelete.append(processor);
    }

    if(totalIndex < (totalCount-1))
    {
        totalIndex++;
    }else
        totalIndex = 0;
}
void App::run()
{
    add_jsonOldProcesses(&prepare_CryptoCompare);
    add_jsonOldProcesses(&prepare_Graviex);
    add_jsonOldProcesses(&prepare_StocksExchange);
    add_jsonOldProcesses(&prepare_Nicehash);
    add_jsonOldProcesses(&prepare_Tradeogre);
    add_jsonOldProcesses(&prepare_Cryptopia);
    add_jsonOldProcesses(&prepare_Octaex);
    add_jsonOldProcesses(&prepare_Tradesatoshi);
    add_jsonOldProcesses(&prepare_QBtc);
    add_jsonOldProcesses(&prepare_Exvo);

    add_rawProcesses(&rawGoJson_MANI);
    add_rawProcesses(&rawGo_VEGI);
    add_rawProcesses(&rawGo_SOLACE);
    add_rawProcesses(&rawGo_PLUS1);
    add_rawProcesses(&rawGo_BTG);
    add_rawProcesses(&rawGo_VRT);
    add_rawProcesses(&rawGo_SONO);
    add_rawProcesses(&rawGo_RVN);
    add_rawProcesses(&rawGo_GRS);
    add_rawProcesses(&rawGo_FTC);
    add_rawProcesses(&rawGo_CREA);
    add_rawProcesses(&rawGo_MSR);
    add_rawProcesses(&rawGo_RTO);
    add_rawProcesses(&rawGo_DERO);
    add_rawProcesses(&rawGo_ETN);
    add_rawProcesses(&rawGo_GRFT);
    add_rawProcesses(&rawGo_XHV);
    add_rawProcesses(&rawGo_IPBC);
    add_rawProcesses(&rawGo_ITNS);
    add_rawProcesses(&rawGo_KRB);
    add_rawProcesses(&rawGo_NCP);
    add_rawProcesses(&rawGo_OMB);
    add_rawProcesses(&rawGo_PLURA);
    add_rawProcesses(&rawGo_QWC);
    add_rawProcesses(&rawGo_SPOT);
    add_rawProcesses(&rawGo_XTL);
    add_rawProcesses(&rawGo_TRTL);
    add_rawProcesses(&rawGo_XUN);
    add_rawProcesses(&rawGo_VAY);
    add_rawProcesses(&rawGo_WTIP);
    add_rawProcesses(&rawGo_EDL);
    add_rawProcesses(&rawGo_GAME);
    add_rawProcesses(&rawGo_ACH);
    add_rawProcesses(&rawGo_ZLS);
    add_rawProcesses(&rawGo_LTC);
    add_rawProcesses(&rawGo_DASH);
    add_rawProcesses(&rawGo_STRAT);
    add_rawProcesses(&rawGo_BTC);



    qDebug()<<"Type 's' for a single all-refresh, type 'a' for an auto-refresh engine start.";
    QTextStream s(stdin);
    option = s.readLine().at(0);

    if(QChar('s') == option)
    {
        qDebug()<<"Singleshot job started.";
        execute_jsonOldProcesses();
        execute_rawProcesses();
    }else
    if(QChar('a') == option)
    {
        qDebug()<<"Autorefresh job started.";
        totalCount = jsonOldCount+rawCount;
        uint32_t toDivide = 10*60/totalCount;

        timer->start(toDivide*1000);
    }
}
void App::end()
{
    qDebug()<<"Job finished.";
    if(QChar('s') == option) emit finished();
    else{
        if(!rawProcessesToDelete.isEmpty())
            for(int i=0;i<1;i++) delete rawProcessesToDelete[i];
    }
}
void App::execute_jsonOldProcesses()
{
    printer->addObjectCounts(jsonOldCount);

    for (int i = 0; i<jsonOldProcesses.size(); i++)
    {
        jsoner.executeProcesses( (*jsonOldProcesses[i])() );
    }
}
void App::add_jsonOldProcesses(QMap<QString, QVariant>(*arg)(void))
{
    jsonOldProcesses.append(arg);
    jsonOldCount++;
}
void App::add_rawProcesses(QList< QMap<QString, QString> >(*arg)(void))
{
    rawProcesses.append((*arg)());
    rawCount++;
}
void App::execute_rawProcesses()
{
    printer->addObjectCounts(rawCount);

    for (int i = 0; i<rawProcesses.size(); i++)
    {
        RawProcessor* processor = new RawProcessor();
        QObject::connect( processor, SIGNAL(goResult(QList< QList< QMap<QString, QVariant> > >*, QString)),
                 printer, SLOT(getResult(QList< QList< QMap<QString, QVariant> > >*, QString)), Qt::QueuedConnection);
        processor->executeProcesses(rawProcesses[i]);
        rawProcessesToDelete.append(processor);
    }
}
QMap<QString, QString> App::prepProc(QString label, QString args)
{
    QMap<QString, QString> temp;
    temp.insert(label, args);
    return temp;
}
QList< QMap<QString, QString> > App::rawGo_BTC()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_STRAT()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_DASH()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_LTC()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_ZLS()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_ACH()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_GAME()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_SONO()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_VRT()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_SOLACE()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGoJson_MANI()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_CREA()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_EDL()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_WTIP()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_FTC()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_GRS()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_RVN()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_BTG()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_PLUS1()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_VEGI()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_VAY()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_XUN()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_TRTL()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_XTL()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_SPOT()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_QWC()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_PLURA()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_OMB()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_NCP()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_KRB()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_ITNS()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_IPBC()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_XHV()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_GRFT()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_ETN()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_DERO()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_MSR()
{
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
    return processes;
}
QList< QMap<QString, QString> > App::rawGo_RTO()
{
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
    return processes;
}
QMap<QString, QVariant> App::prepare_CryptoCompare()
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
QMap<QString, QVariant> App::prepare_Exvo()
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
QMap<QString, QVariant> App::prepare_QBtc()
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
QMap<QString, QVariant> App::prepare_Tradesatoshi()
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
QMap<QString, QVariant> App::prepare_Octaex()
{
    QMap<QString, QVariant> processes;
    processes.insert( "0#name", "Octaex");
    processes.insert( "1#type", "exchange");
    processes.insert( "2#pretickers", "https://www.octaex.com/api/trade/all/");
    processes.insert( "3#functiononly", "objlist(pairName|non|new_price&price|max_price&high|min_price&low|amount&vol|buy_price&buy|sell_price&sell),append()" );
    processes.insert( "4#result", "");
    return processes;
}
QMap<QString, QVariant> App::prepare_Cryptopia()
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
QMap<QString, QVariant> App::prepare_Tradeogre()
{
    QMap<QString, QVariant> processes;
    processes.insert( "0#name", "Tradeogre");
    processes.insert( "1#type", "exchangeinverted");
    processes.insert( "2#pretickers", "https://tradeogre.com/api/v1/markets");
    processes.insert( "3#functiononly", "array(),mapobjlist(pairName|price&price|high&high|low&low|volume&vol|bid&buy|ask&sell),append()" );
    processes.insert( "4#result", "");
    return processes;
}
QMap<QString, QVariant> App::prepare_Nicehash()
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
QMap<QString, QVariant> App::prepare_Graviex()
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
QMap<QString, QVariant> App::prepare_StocksExchange()
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
