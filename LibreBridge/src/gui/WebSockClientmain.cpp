#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include "WebSockClient.hpp"

int WebSockClientmain(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("QtWebSockets example: WebSockClient");
    parser.addHelpOption();

    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
            QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);
    parser.process(a);
    bool debug = parser.isSet(dbgOption);

    WebSockClient client(QUrl(QStringLiteral("ws://localhost:8000")), debug);
    QObject::connect(&client, &WebSockClient::closed, &a, &QCoreApplication::quit);

    return a.exec();
}


