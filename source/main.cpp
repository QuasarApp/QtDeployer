#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QTranslator>

#include "CPP/cppmanager.h"
#include "CPP/mainmanager.h"
#include "CPP/outputmanager.h"
#include "CPP/pluginmanager.h"
#include "CPP/qmlmanager.h"

bool loadTr(QGuiApplication &app){
    QTranslator translator;

    QString defaultLocale = QLocale::system().name();
    defaultLocale.truncate(defaultLocale.lastIndexOf('_'));

    if(!translator.load(QString(":/languages/%0").arg(defaultLocale))){
        return false;
    }
    app.installTranslator(&translator);

    return true;

}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    app.setWindowIcon(QIcon("://icon"));

    loadTr(app);

    CppManager C;
    QmlManager Q;
    PluginManager P;
    OutputManager O;

    MainManager M(&C, &Q, &O, &P);

    QQmlApplicationEngine engine;

    auto *R = engine.rootContext();
    R->setContextProperty("CppManager", &C);
    R->setContextProperty("QmlManager", &Q);
    R->setContextProperty("PluginManager", &P);
    R->setContextProperty("MainManager", &M);
    R->setContextProperty("OutputManager", &O);


    engine.load(QUrl(QLatin1String("qrc:/QML/main.qml")));
    if (engine.rootObjects().isEmpty()) return -1;

    return app.exec();
}
