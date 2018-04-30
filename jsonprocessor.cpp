#include "jsonprocessor.h"
#include <QDebug>
#include <QTextCodec>

void JsonProcessor::test()
{
    QNetworkRequest request(QUrl( "https://msrchain.net/" ));
    networkAccess->get(request)->setProperty("test", "on");

}
JsonProcessor::JsonProcessor(QObject *parent) : QObject(parent)
{
    networkAccess = new QNetworkAccessManager(this);


    connect(networkAccess, SIGNAL(finished(QNetworkReply*)), this, SLOT(replied(QNetworkReply*)));
}
void JsonProcessor::executeProcesses(QMap<QString, QVariant> processes)
{
    Process process;
    process.index = 2;
    process.processes = processes;

    QString name = getFullKeyName( "name", process.processes.keys() );
    process.type = processes.value(getFullKeyName( "type", process.processes.keys() )).toString();

    tracker.insert( processes.value(name).toString() , process );


    executeProcess( processes.value(name).toString() );
}
void JsonProcessor::executeProcess(QString name)
{
    int current = tracker[name].index++;
    QString order = getOnlyKeyName( current, tracker[name].processes.keys() );
    QString proc = getFullKeyName( current, tracker[name].processes.keys() );

    if( order == QString("pretickers") )
    {
        QNetworkRequest request(QUrl( tracker[name].processes.value(proc).toString() ));
        networkAccess->get(request)->setProperty("name", name);
    }else
    if( order == QString("markets") )
    {
        QString argsKey = getFullKeyName( ++current, tracker[name].processes.keys() );
        tracker[name].result.append(jsonThroughInstruction(tracker[name].processes.value(argsKey).toString(), buffor[name], nullptr));

        tracker[name].index++;

        //pretickers RESULT ABOVE

        QNetworkRequest request(QUrl( tracker[name].processes.value(proc).toString() ));
        networkAccess->get(request)->setProperty("name", name);
    }else
    if( order == QString("functiononly") )
    {
        jsonThroughInstruction(tracker[name].processes.value(proc).toString(), buffor[name], &(tracker[name].result));
        executeProcess(name);
    }else
    if( order == QString("result") )
    {
        emit goResult(&tracker[name].result,name + QString('~') + tracker[name].type);
    }else
    if( order == QString("text") )
    {
        QString instructionBuffor = tracker[name].processes.value(proc).toString();
        /*      */QList<QStringList> instructions = getInstructionsList( instructionBuffor, ',', '(', ')' );

        QString data = QString(rawBuffor[name]);
        QString itsExpr;

        QStringList args;
        if(instructions.at(0).at(1).contains("|"))
        {
            QStringList allData = instructions.at(0).at(1).split("|");
            args = allData.at(0).split("&");
            itsExpr = allData.at(1);
        }else
            args = instructions.at(0).at(1).split("&");

        if(!itsExpr.isEmpty())
        {
            QRegularExpression re("(Hash rate:) (.*) (.*)(s)");

            QRegularExpressionMatch match = re.match(data);
            if (match.hasMatch()) {
                int startOffset = match.capturedStart(); // startOffset == 6
                int endOffset = match.capturedEnd(); // endOffset == 9
                double nmb;
                qDebug()<<(nmb = data.mid(startOffset+11, endOffset-9-startOffset-12).toDouble());
                // ...
                qDebug()<<nmb;
            }else{
                qDebug()<<match.isValid();
            }

        }
        executeProcess(name);

        QMap<QString, QVariant>* tickerPointer;
        if( (tickerPointer = specifyVariantMapByChosenLabel(tracker[name].returnBuffer,args.at(1),args.at(0))) != nullptr )
        {
            tickerPointer->operator [](instructions.at(0).at(0)) = data;
            //tickerPointer->operator [](args.at(1)) = args.at(0);
        }else{
            QMap<QString, QVariant> ticker;
            ticker[instructions.at(0).at(0)] = data;
            ticker[args.at(1)] = args.at(0);
            tracker[name].returnBuffer.append(ticker);
        }

        executeProcess(name);
    }else
    if( order == QString("raw") )
    {
        QString instructionBuffor = tracker[name].processes.value(proc).toString();
        /*      */QList<QStringList> instructions = getInstructionsList( instructionBuffor, ',', '(', ')' );

        QString data = QString(rawBuffor[name]);
        QStringList args = instructions.at(0).at(1).split("&");

        QMap<QString, QVariant> ticker;
        ticker[instructions.at(0).at(0)] = data;
        ticker[args.at(1)] = args.at(0);
        tracker[name].returnBuffer.append(ticker);

        executeProcess(name);
    }else
    if( order == QString("resultappend") )
    {
        tracker[name].result.append(tracker[name].returnBuffer);

        executeProcess(name);
    }
}
QMap<QString, QVariant>* JsonProcessor::specifyVariantMapByChosenLabel(QList< QMap<QString, QVariant> >& list, QString label, QString arg)
{
    for(auto i = list.begin(); i != list.end(); ++i)
    {
        if( (*i).contains(label) && ((*i).value(label).toString() == arg))
        {
            return &*i;
        }
    }
    return nullptr;
}
QString JsonProcessor::getFullKeyName(QString key, QStringList&& list)
{
    foreach (QString item, list) {
        if( item.split('#').at(1) == key)
        {
            return item;
        }
    }
    return QString("");
}
QString JsonProcessor::getFullKeyName(int index, QStringList&& list)
{
    QString key = QString::number(index);

    foreach (QString item, list) {
        if( item.split('#').at(0) == key)
        {
            return item;
        }
    }
    return QString("");
}
QString JsonProcessor::getOnlyKeyName(int index, QStringList&& list)
{
    QString key = QString::number(index);

    foreach (QString item, list) {
        if( item.split('#').at(0) == key)
        {
            return item.split('#').at(1);
        }
    }
    return QString("");
}
void JsonProcessor::replied(QNetworkReply* reply)
{
    QByteArray responseData = reply->readAll();

    if(!reply->property("test").isNull())
    {
        QString theCode = QString(responseData);
        qDebug()<<theCode;
        return;
    }

    QString father = reply->property("name").toString(); //certainly not mine
    reply->deleteLater();

    if(father.contains("=text"))
    {
        rawBuffor.insert(father, responseData);
    }

    buffor.insert(father , QJsonDocument::fromJson(responseData) );
    executeProcess(father); //shall be async?
    buffor.remove(father);

    if(!rawBuffor.isEmpty())
    {
        rawBuffor.remove(father);
    }
}
QList< QMap<QString, QVariant> > JsonProcessor::jsonThroughInstruction(QString instructionList, QJsonDocument& doc, QList< QList< QMap<QString, QVariant> > >* result)
{
    QList< QMap<QString, QVariant> > ret;

    QList<QStringList> instructions = getInstructionsList( instructionList, ',', '(', ')' );

    QJsonValue val;
    QJsonArray arr;
    QJsonObject obj;
    QVariant varian;
    for(int i=0; i<instructions.size(); i++)
    {
        if(instructions.at(i).at(0) == "array")
        {
            arr = doc.array();
        }else
        if(instructions.at(i).at(0) == "valarray")
        {
            arr = val.toArray();
        }else
        if(instructions.at(i).at(0) == "valargs")
        {
            QStringList args = instructions.at(i).at(1).split('|');
            if(args.at(1) == QString("non"))
            {
                val = doc[args.at(0)];
            }else
                val = doc[args.at(0)][args.at(1)];
        }else
        if(instructions.at(i).at(0) == "variantlist")
        {
            QStringList args = instructions.at(i).at(1).split('|');
            foreach (QVariant item, arr.toVariantList()){
                QMap<QString, QVariant> ticker;
                foreach (QString labelPair, args) {
                    QStringList labs = labelPair.split('&');
                    ticker.insert( labs.at(1) , item.toMap()[labs.at(0)].toString() );
                }
                ret.append(ticker);
            }
        }else
        if(instructions.at(i).at(0) == "mergebyreferencedocwithpreparameter")
        {
            QStringList args = instructions.at(i).at(1).split('|');

            QString id = args.at(0);

            QString preParameter = args.at(1);
            if(!preParameter.contains('&')) args.pop_front();

            args.pop_front();

            for(int i=0;i<result->at(0).size();i++) {
                    QMap<QString, QVariant>* ticker = &(result->operator [](0)[i]);

                    QJsonValue obj = doc[ticker->value(id).toString()];
                    if(!obj.isUndefined())
                    {
                        foreach (QString labelPair, args) {
                            QStringList labs = labelPair.split('&');
                            if(!preParameter.contains('&'))
                            {
                                ticker->insert( labs.at(1) , obj[preParameter][labs.at(0)].toString() );
                            }else{
                                ticker->insert( labs.at(1) , obj[labs.at(0)].toString() );
                            }
                        }
                        QJsonDocument temp(obj.toObject());
                        ticker->insert( "raw", QString(temp.toJson(QJsonDocument::Compact)));
                    }
                }
        }else
        if(instructions.at(i).at(0) == "non")
        {

        }else
        if(instructions.at(i).at(0) == "variantlistmerge")
        {
            QStringList args = instructions.at(i).at(1).split('|');
            QString pre = args.at(0);
            QString tho = args.at(1);
            args.pop_front();
            args.pop_front();

            foreach (QVariant item, arr.toVariantList()){
                QMap<QString, QVariant>* ticker = nullptr;
                for(int i=0;i<result->at(0).size();i++)
                {
                    if(result->operator [](0)[i].value(tho) == item.toMap()[pre].toString())
                    {
                        ticker = &(result->operator [](0)[i]);
                        break;
                    }
                }

                foreach (QString labelPair, args) {
                    QStringList labs = labelPair.split('&');
                    ticker->insert( labs.at(1) , item.toMap()[labs.at(0)].toString() );
                }
            }
        }else
        if(instructions.at(i).at(0) == "mapobjlist")
        {
            QStringList args = instructions.at(i).at(1).split('|');
            QString arg = args.at(0);
            args.pop_front();

            foreach (QVariant item, arr.toVariantList()){
                QMap<QString, QVariant> ticker;
                ticker.insert( arg, item.toMap().keys().at(0) );

                QJsonObject mapObj = item.toMap().value(ticker.value(arg).toString()).toJsonObject();
                foreach (QString labelPair, args) {
                    QStringList labs = labelPair.split('&');
                    ticker.insert( labs.at(1) , mapObj.toVariantMap()[labs.at(0)].toString() );
                }
                ret.append(ticker);
            }
        }else
        if(instructions.at(i).at(0) == "append")
        {
           result->append(ret);
        }else
        if(instructions.at(i).at(0) == "objlist")
        {
            QStringList args = instructions.at(i).at(1).split('|');
            QString arg = args.at(0);
            QString secArg = args.at(1);
            args.pop_front();
            args.pop_front();

            QStringList allTickers;
            if( (i > 0) && (instructions.at(i-1).at(0) == "doctovariant"))
            {
                allTickers = val.toVariant().toMap().keys();
            }else
                allTickers = doc.toVariant().toMap().keys();

            foreach (QString item, allTickers){
                QMap<QString, QVariant> ticker;
                ticker.insert( arg, item );

                QJsonObject mapObj;
                if(secArg != "non")
                {
                    if( (i > 0) && (instructions.at(i-1).at(0) == "doctovariant"))
                    {
                        mapObj =  val[item][secArg].toObject();
                    }else
                        mapObj =  doc[item][secArg].toObject();
                }else
                {
                    if( (i > 0) && (instructions.at(i-1).at(0) == "doctovariant"))
                    {
                        mapObj =  val[item].toObject();
                    }else
                        mapObj =  doc[item].toObject();
                }

                foreach (QString labelPair, args) {
                    QStringList labs = labelPair.split('&');
                    ticker[ labs.at(1) ] = mapObj.toVariantMap()[labs.at(0)].toString();
                }
                ret.append(ticker);
            }
        }else
        if(instructions.at(i).at(0) == "doctovariant")
        {

        }
    }

    return ret;
}
QList<QStringList> JsonProcessor::getInstructionsList(QString& instructionList, char insSep, char argSepA, char argSepB)
{
    QList<QStringList> all;

    QStringList instructions = instructionList.split(insSep);

    foreach (QString fullInstruction, instructions) {
        QStringList full = fullInstruction.split(argSepA);
        if( full.at(1).endsWith(argSepB) )
        {
            full[1] = full[1].left( full[1].size() - 1 );
        }

        all.append(full);
    }

    return all;
}




















