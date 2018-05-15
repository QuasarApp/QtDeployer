#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QTranslator>
#include <QFont>
#include <QFontDatabase>
#include <iostream>

#include "CPP/cppmanager.h"
#include "CPP/mainmanager.h"
#include "CPP/outputmanager.h"
#include "CPP/pluginmanager.h"
#include "CPP/qmlmanager.h"

void setFont(const QGuiApplication& app){

    QString fontPath = "://ubuntu";
    int fontId = QFontDatabase::addApplicationFont(fontPath);
    if (fontId != -1)
    {
        QFont font(QFontDatabase::applicationFontFamilies(fontId).at(0));
        app.setFont(font);
    }
}

bool initLocale(const QString &locale, QGuiApplication& app, QTranslator &translator){

    QString defaultLocale = QLocale::system().name();
    defaultLocale.truncate(defaultLocale.lastIndexOf('_'));

    if(!locale.isEmpty() && translator.load(QString(":/languages/%0").arg(locale))){
        return app.installTranslator(&translator);
    }

    if(!translator.load(QString(":/languages/%0").arg(defaultLocale))){
        return false;
    }

    return app.installTranslator(&translator);
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    setFont(app);

    QTranslator translator;

    QString locale = "";

    app.setWindowIcon(QIcon("://icon"));

    if(!initLocale(locale, app, translator)){
        std::cout << "error load language : " << locale.toStdString() <<std::endl;
    }

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
