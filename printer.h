#ifndef PRINTER_H
#define PRINTER_H

#include <QCoreApplication>
#include <QObject>
#include <QSqlDatabase>
#include <QDebug>
#include <QVariant>
#include <QMap>

class Printer : public QObject
{
    Q_OBJECT
private:
    QSqlDatabase database;
    QString method;
    bool standarizationAllowed;
    bool invertedAllowed;
    bool remove;

    int objectCount;
private:
    QString makeValue(QString data);
    void setupDatabase();
    void purgeList(QList< QMap<QString, QVariant> >* list, QStringList toPurge, QString what);
    QString prepareSQLColumns(QStringList columns);
    QString prepareSQLValue(int index, QList< QMap<QString, QVariant> >* list,  QStringList columns, QString customizePart);
    QString prepareSQLUpdate(int index, QList< QMap<QString, QVariant> >* list,  QStringList columns, QString customizePart);
    void standardPairing(QString& value);
    void standardKeys(QList< QMap<QString, QVariant> >* list,  QString name);
    void pushWithExchanges(QList< QMap<QString, QVariant> >* list,  QString name);
    void pushWithHashes(QList< QMap<QString, QVariant> >* list,  QString name);
    void printListFor(QList< QMap<QString, QVariant> >* list,  QString name);
    //2nd - index column=key (for WHERE clasure), 3rd - table name, 4th/5th column to append NAME/value
    void insertAndAppendIfNotExist(QList< QMap<QString, QVariant> >* list, QString referenceColumn,
                                   QString tableName, QString appColumn, QString name);
    void purgeSubValue(QMap<QString, QVariant>* item, QString key);

public:
    Printer(QObject *parent = nullptr);
    Printer(QString choice, QObject *parent = nullptr);

    void addObjectCounts(int count);
    void setRemove(bool removeArg);

    ~Printer();
signals:
    void pleaseEnd();
public slots:
    void getResult(QList< QList< QMap<QString, QVariant> > >* result, QString name);
};

#endif // PRINTER_H
