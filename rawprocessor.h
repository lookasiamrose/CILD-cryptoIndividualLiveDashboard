#ifndef RAWPROCESSOR_H
#define RAWPROCESSOR_H

#include <QObject>
#include <QVariant>
#include <QMap>
#include <QtNetwork>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

class RawProcessor : public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager* networkAccess;

    quint16 currentProccess;
    QList< QMap<QString, QString> > processes;
    QList<QRegularExpression> regexs;
    QString name;
    QString type;
    QList< QList< QMap<QString, QVariant> > > resultRef;
    QList< QMap<QString, QVariant> > result;

    QByteArray dataArray;
public:
    explicit RawProcessor(QObject *parent = nullptr);
    void executeProcesses(QList< QMap<QString, QString> > processesArg);
    void executeProcess(QByteArray data = QByteArray());
signals:
    void goResult(QList< QList< QMap<QString, QVariant> > >*, QString);
public slots:
    void networkReply(QNetworkReply* reply);
protected:
    void insertValAndLab(QString resultString, QString label);
};

#endif // RAWPROCESSOR_H
