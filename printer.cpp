#include "printer.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

void Printer::addObjectCounts(int count)
{
    objectCount += count;
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
    QString databasePath = QCoreApplication::applicationDirPath() + QString("/") + QString("databaserev1.accdb");
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
            QStringList args = name.split('~');
            if(args.at(1) == "exchange")
            {
                standarizationAllowed = true;
                pushWithExchanges(list, args.at(0));
                standarizationAllowed = false;
            }else
            if(args.at(1) == "exchangeinverted")
            {
                invertedAllowed = true;
                standarizationAllowed = true;
                pushWithExchanges(list, args.at(0));
                standarizationAllowed = false;
                invertedAllowed = false;
            }else
            if(args.at(1) == "hash")
            {
                pushWithHashes(list, args.at(0));
            }else
            if(args.at(1) == "coinsdata")
            {
                insertAndAppendIfNotExist(list, "symbol", "Coins", QString(""), name);
            }
            if(args.at(1) == "mining")
            {
                insertAndAppendIfNotExist(list, "symbol", "Mining", QString(""), name);
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
    if(list->size() == 0)
    {
        qDebug()<<("Error: no new data for " + name);
        return;
    }

    QSqlQuery query(database);
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
