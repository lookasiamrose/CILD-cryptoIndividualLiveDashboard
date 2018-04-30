#ifndef COIN_H
#define COIN_H

#include <QObject>

class Coin : public QObject
{
    Q_OBJECT
public:
    explicit Coin(QObject *parent = nullptr);

signals:

public slots:
};

#endif // COIN_H