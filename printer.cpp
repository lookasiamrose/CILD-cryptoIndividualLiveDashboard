#include "printer.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

void Printer::addObjectCounts(int count)
{
    objectCount += count;
}
void Printer::setRemove(bool removeArg)
{
    remove = removeArg;
}
void Printer::standardPairing(QString& value)
{
    if(standarizationAllowed){
        if(value.contains('-'))
        {
            value.replace('-','/');
        }else
        if(value.contains('_'))
        {
            value.replace('_','/');
        }else
        if(value.contains('\\'))
        {
            value.replace('\\','/');
        }
    }
    if(invertedAllowed){
        QStringList pairs = value.split('/');
        value = pairs.at(1) + QString('/') + pairs.at(0);
    }
}
void Printer::standardKeys(QList< QMap<QString, QVariant> >* list,  QString name)
{
    for(auto i = list->begin(); i != list->end(); ++i)
    {
        if( (*i).contains("id") )
        {
            (*i).insert(name + "_id", (*i).value("id"));
            (*i).remove("id");
        }
        if( (*i).contains("name") )
        {
            (*i).insert(name + "_name", (*i).value("name"));
            (*i).remove("name");
        }
    }
}
Printer::Printer(QObject *parent) : QObject(parent)
{
    objectCount = 0;

    remove = false;
    invertedAllowed = false;
    standarizationAllowed = false;
    setupDatabase();
    method = QString("console");
}
Printer::Printer(QString choice, QObject *parent) : Printer(parent)
{
    method = choice;
}
void Printer::setupDatabase()
{
    QString databasePath = QCoreApplication::applicationDirPath() + QString("/") + QString("database.1.1.0.accdb");
    database = QSqlDatabase::addDatabase("QODBC","connection");
    database.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)}; DSN=''; READONLY=FALSE; DBQ=" + databasePath);
}
void Printer::getResult(QList< QList< QMap<QString, QVariant> > >* result, QString name)
{
    QList< QMap<QString, QVariant> >* list = &(result->operator [](0));
    if(method == QString("console"))
    {
        printListFor(list, name);
    }else
    if(method == QString("database"))
    {
        if( database.open() )
        {          
            QStringList toPurgeMARKETS;
            toPurgeMARKETS.append("price");
            toPurgeMARKETS.append("buy");
            toPurgeMARKETS.append("sell");
            toPurgeMARKETS.append("low");
            toPurgeMARKETS.append("high");
            toPurgeMARKETS.append("vol");
            toPurgeMARKETS.append("volbtc");
            toPurgeMARKETS.append("last");
            toPurgeMARKETS.append("change");
            QStringList args = name.split('~');
            if(args.at(1) == "exchange")
            {
;
                purgeList(list,toPurgeMARKETS,"value");
                standarizationAllowed = true;
                pushWithExchanges(list, args.at(0));
                standarizationAllowed = false;
            }else
            if(args.at(1) == "exchangeinverted")
            {
                purgeList(list,toPurgeMARKETS,"value");
                invertedAllowed = true;
                standarizationAllowed = true;
                pushWithExchanges(list, args.at(0));
                standarizationAllowed = false;
                invertedAllowed = false;
            }else
            if(args.at(1) == "hash")
            {
                QStringList toPurge;
                toPurge.append("price");
                toPurge.append("diff");
                toPurge.append("limit");
                toPurge.append("initial_minimum_diff");
                toPurge.append("working_minimum");
                purgeList(list,toPurge,"value");
                pushWithHashes(list, args.at(0));
            }else
            if(args.at(1) == "coinsdata")
            {
                QStringList toPurge;
                toPurge.append("supply");
                purgeList(list,toPurge,"value");
                insertAndAppendIfNotExist(list, "symbol", "Coins", QString(""), name);
            }else
            if(args.at(1) == "mining")
            {
                QStringList toPurge;
                toPurge.append("reward");
                toPurge.append("difficulty");
                purgeList(list,toPurge,"value");
                insertAndAppendIfNotExist(list, "symbol", "Mining", QString(""), name);
            }else
            if(args.at(1) == "whattomine")
            {
                QStringList toPurge;
                toPurge.append("block_time");
                toPurge.append("hashrate");
                toPurge.append("reward");
                toPurge.append("difficulty");
                purgeList(list,toPurge,"value");
                insertAndAppendIfNotExist(list, "symbol", "WhatToMine", QString(""), name);
            }
        }else{
            qDebug()<<database.lastError().text();
        }
    }
    if(objectCount > 1)
    {
            objectCount--;
            qDebug()<<"[DEBUG] "<<"Data batches to print: "<<objectCount;
    }else{
            emit pleaseEnd();
    }
}
QString Printer::makeValue(QString data)
{
    if(data.contains(' '))
        data.remove(' ');
    if(data.contains(','))
        data.remove(',');
    if(data.contains('.'))
        data.replace('.',',');
    return data;
}
void Printer::purgeSubValue(QMap<QString, QVariant>* item, QString key)
{
    if(item->keys().contains(key))
    {
        QString val = item->value(key).toString();
        val = makeValue(val);
        item->operator [](key) = QVariant::fromValue(val);
    }
}

void Printer::purgeList(QList< QMap<QString, QVariant> >* list, QStringList toPurge, QString what)
{
    if(!toPurge.isEmpty())
    {
        for(int i=0;i<list->size();i++)
        {
            foreach (QString varRemove, toPurge)
            {
                if(what == QString("value")) purgeSubValue(&(list->operator [](i)), varRemove);
            }
        }
    }
}
void Printer::printListFor(QList< QMap<QString, QVariant> >* list,  QString name)
{
    qDebug()<<" - - - - "<<name;
    for(int i=0;i<list->size();i++) {
        QStringList keys = list->operator [](i).keys();
        foreach (QString key, keys) {
            qDebug()<<key<<" - "<<list->operator [](i).value(key).toString();
        }
    }
}
void Printer::pushWithHashes(QList< QMap<QString, QVariant> >* list,  QString name)
{
    standardKeys(list, name);
    insertAndAppendIfNotExist(list, name + "_id", "Hash", QString(""), name);
}
void Printer::pushWithExchanges(QList< QMap<QString, QVariant> >* list,  QString name)
{
    insertAndAppendIfNotExist(list, "pairName", "Markets", "Market", name);
}
void Printer::insertAndAppendIfNotExist(QList< QMap<QString, QVariant> >* list, QString referenceColumn,
                                        QString tableName, QString appColumn, QString name)
{
    QSqlQuery query(database);
    if(remove)
    {
        if(!appColumn.isEmpty())
        {
            query.exec(QString("DELETE FROM " + tableName)
                    + QString(" WHERE ") + appColumn + QString("='") + name + QString("'")
                    + QString(';'));
        }else{
            if(QString("Mining") != tableName)
            {
                query.exec(QString("DELETE FROM " + tableName) + QString(';'));
            }
        }
        //qDebug()<<"[DEBUG] "<<query.lastQuery();
    }
    query.clear();
    if(list->size() == 0)
    {
        qDebug()<<"[DEBUG] "<<("Error: no new data for " + name);
        return;
    }

    QStringList keys = list->at(0).keys();

    query.exec(QString("SELECT " + referenceColumn + " FROM " + tableName)
                + ( !appColumn.isEmpty() ? QString(" WHERE " + appColumn + " ='" + name + "'") : QString("") )
                + QString(';'));
    //qDebug()<<query.lastError().text();
    //qDebug()<<"----------------------------------------------------------------------";

    QSqlQuery update(database);
    int rowsToCheck = 0;
    int rowsToUpdate = 0;
    while (query.next()) {
        QString pairName = query.value(0).toString();
        for(int i=0;i<list->size();i++)
        {
            QString listPairName = list->at(i).value(referenceColumn).toString();
            standardPairing(listPairName);
            if(listPairName == pairName)
            {
                rowsToUpdate++;
                update.exec( QString("UPDATE " + tableName + " SET") + prepareSQLUpdate(i, list, keys, referenceColumn)
                            + ( !appColumn.isEmpty() ? QString(", " + appColumn + " = '" + name + "'") : QString("") )
                            + QString(" WHERE " + referenceColumn + " = '") + pairName
                            + ( !appColumn.isEmpty() ? QString("' AND " + appColumn + " = '" + name) : QString("") )
                            + QString("';") );
                //qDebug()<<update.lastError().text();
                //qDebug()<<update.lastQuery();
                list->removeAt(i);
                break;
            }
        }
        rowsToCheck++;
    }
    //qDebug()<<"----------------------------------------------------------------------";
    qDebug()<<("'" + tableName + "' table data check for '" + name + "', " + QString::number(rowsToCheck) + " rows already inserted" );
    qDebug()<<("'" + tableName + "' table data update for '" + name + "', " + QString::number(rowsToUpdate) + " rows updated" );
    query.clear();

    QString columns = prepareSQLColumns(keys);
    if(!appColumn.isEmpty()){
        columns.append(QString(", ") + appColumn);
    }
    QString vals = QString("");
    int rowsToInsert = 0;
    for(int i=0;i<list->size();i++)
    {
        vals = QString('(') + prepareSQLValue(i, list, keys, referenceColumn)
             + ( !appColumn.isEmpty() ? QString(", '" + name + "'") : QString("") )
             + QString(')');
        query.exec( QString("INSERT INTO " + tableName + "(") + columns
                  + QString(") VALUES ") + vals + QString(";"));
        rowsToInsert++;
    }
    //qDebug()<<query.lastError().text();
    //qDebug()<<query.lastQuery();

    qDebug()<<("'" + tableName + "' table data insert for '" + name + "', " + QString::number(rowsToInsert) + " rows inserted" );
    query.clear();
}
QString Printer::prepareSQLUpdate(int index, QList< QMap<QString, QVariant> >* list,  QStringList columns, QString customizePart)
{
    QString vals = QString("");

    for(auto i = columns.begin(); i != columns.end(); ++i)
    {
        QString value = list->at(index).value(*i).toString();
        if( !customizePart.isEmpty() && (*i) == customizePart)
        {
            standardPairing(value);
        }
        vals.append(QString(' ') + (*i) + QString(" = '") + value + QString("',"));
    }
    vals.remove(vals.lastIndexOf(','),1);

    return vals;
}
QString Printer::prepareSQLValue(int index, QList< QMap<QString, QVariant> >* list,  QStringList columns, QString customizePart)
{
    QString vals = QString("");

    for(auto i = columns.begin(); i != columns.end(); ++i)
    {
        QString value = list->at(index).value(*i).toString();
        if( !customizePart.isEmpty() && (*i) == customizePart)
        {
            standardPairing(value);
        }
        vals.append(QString(" '") + value + QString("',"));
    }
    vals.remove(vals.lastIndexOf(','),1);

    return vals;
}
QString Printer::prepareSQLColumns(QStringList columns)
{
    QString cols = QString("");

    for(auto i = columns.begin(); i != columns.end(); ++i)
    {
        cols.append(QString(' ') + (*i) + QString(','));
    }
    cols.remove(cols.lastIndexOf(','),1);

    return cols;
}
Printer::~Printer()
{
    if(database.isOpen()) database.close();
}
