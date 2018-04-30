#ifndef JSONPROCESSOR_H
#define JSONPROCESSOR_H

#include <QObject>
#include <QVariant>
#include <QMap>
#include <QtNetwork>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

class JsonProcessor : public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager* networkAccess;
    QMap<QString, QJsonDocument> buffor;
    QMap<QString, QByteArray> rawBuffor;

    class Process{
    public:
        int index;
        QMap<QString, QVariant> processes;
        QList< QList< QMap<QString, QVariant> > > result;
        QList< QMap<QString, QVariant> > returnBuffer;
        QString type;
    };
    QMap<QString, Process> tracker;
private:
    QString getFullKeyName(QString key, QStringList&& list);
    QString getFullKeyName(int index, QStringList&& list);
    QString getOnlyKeyName(int index, QStringList&& list);
    void executeProcess(QString name);
    QMap<QString, QVariant>* specifyVariantMapByChosenLabel(QList< QMap<QString, QVariant> >& list, QString label, QString arg);
public:
    void test();
    explicit JsonProcessor(QObject *parent = nullptr);
    void executeProcesses(QMap<QString, QVariant> processes);
    QList< QMap<QString, QVariant> > jsonThroughInstruction(QString instructionList, QJsonDocument& doc, QList< QList< QMap<QString, QVariant> > >* result = nullptr);
    QList<QStringList> getInstructionsList(QString& instructionList, char insSep, char argSepA, char argSepB);
    ~JsonProcessor() {  }
signals:
    void goResult(QList< QList< QMap<QString, QVariant> > >*, QString);
public slots:
    void replied(QNetworkReply* reply);
};

#endif // JSONPROCESSOR_H
