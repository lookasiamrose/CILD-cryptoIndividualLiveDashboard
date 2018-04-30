#include <QCoreApplication>

#include "app.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    App* app = new App(&a);
    QObject::connect(app, SIGNAL(finished()), &a, SLOT(quit()));

    QTimer::singleShot(0, app, SLOT(run()));
    return a.exec();
}
