#include <QCoreApplication>
#include "jsonserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    JSONserver server;

    return a.exec();
}
