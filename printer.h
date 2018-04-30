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
private:
    void setupDatabase();
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
public:
    Printer(QObject *parent = nullptr);
    Printer(QString choice, QObject *parent = nullptr);
    ~Printer();
signals:

public slots:
    void getResult(QList< QList< QMap<QString, QVariant> > >* result, QString name);
};

#endif // PRINTER_H
