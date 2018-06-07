#include "rawprocessor.h"
#include <QDateTime>

RawProcessor::RawProcessor(QObject *parent) : QObject(parent)
{
    currentProccess = 0;

    networkAccess = new QNetworkAccessManager(this);
    connect(networkAccess, SIGNAL(finished(QNetworkReply*)), this, SLOT(networkReply(QNetworkReply*)));
}
void RawProcessor::executeProcesses(QList< QMap<QString, QString> > processesArg)
{
    if(processesArg.isEmpty()) {qDebug()<<"issue, RawProcessor::executeProcesses";return;}

    processes = processesArg;
    executeProcess();
}
void RawProcessor::insertValAndLab(QString resultString, QString label)
{
    if(result.isEmpty())
    {
        QMap<QString, QVariant> temp;
        temp[label] = QVariant(resultString);
        result.append(temp);
    }else
    {
        result[0][label] = QVariant(resultString);
    }
}

void RawProcessor::executeProcess(QByteArray data)
{
    if(!data.isEmpty())
    {
        dataArray = data;
    }

    QMap<QString, QString> current = processes[currentProccess++];
    if( current.keys().at(0) == QString("result") )
    { 
        resultRef.append(result);
        emit goResult( &resultRef, name + QString('~') + type);
        return;
    }else
    if( current.keys().at(0) == QString("request") )
    {
        QNetworkRequest request(QUrl( current.value(current.keys().at(0)) ));
        networkAccess->get(request); //->setProperty("name", "name");
        return;
    }else
    if( current.keys().at(0) == QString("text") )
    {
        QString dataString = QString(dataArray);
        QString resultString = dataString;

        while(!regexs.isEmpty())
        {
            QRegularExpressionMatch match = regexs.at(0).match(resultString);
            if (match.hasMatch()){
                int startOffset = match.capturedStart();
                int endOffset = match.capturedEnd();
                resultString = resultString.mid( startOffset, endOffset-startOffset);
                //qDebug()<<"[DEBUG] "<<resultString;
                ///* */qDebug()<<resultString;
            }else{
                qDebug()<<"[DEBUG] "<<match.regularExpression().pattern()<<" - "
                        <<match.regularExpression().errorString();
            }
            regexs.pop_front();
        }

        QString label = current.value(current.keys().at(0));

        insertValAndLab(resultString.trimmed(), label);

        //qDebug()<<resultString;
    }else
    if( current.keys().at(0) == QString("regex") )
    {
        QRegularExpression regex(current.value(current.keys().at(0)));
        regexs.append(regex);
    }else
    if( current.keys().at(0) == QString("name") )
    {
        name = current.value(current.keys().at(0));
    }else
    if( current.keys().at(0) == QString("type") )
    {
        type = current.value(current.keys().at(0));
    }else
    if( current.keys().at(0) == QString("reference") )
    {
        QStringList indexes = current.value(current.keys().at(0)).split('&');
        insertValAndLab(indexes.at(1),indexes.at(0));
    }else
    if( current.keys().at(0) == QString("now") )
    {
        QDateTime now = QDateTime::currentDateTime();
        insertValAndLab(now.toString("yyyy-MM-dd HH:mm:ss"), current.value(current.keys().at(0)));
    }
    else
    if( current.keys().at(0) == QString("") )
    {

    }
    else
    if( current.keys().at(0) == QString("") )
    {

    }


    executeProcess();
}
void RawProcessor::networkReply(QNetworkReply* reply)
{
    QByteArray responseData = reply->readAll();
    reply->deleteLater();

    //QString father = reply->property("name").toString();
    executeProcess(responseData);
}
