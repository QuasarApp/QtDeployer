#include <QtGlobal>

#if (QT_VERSION >= QT_VERSION_CHECK(5, 8, 0))
    #include <QGuiApplication>
    #include <QQmlApplicationEngine>
    #include <QQmlContext>
#else
    #include <QApplication>
    #include "mainwindow.h"
#endif

#include <QIcon>
#include <QTranslator>

#include "CPP/cppmanager.h"
#include "CPP/mainmanager.h"
#include "CPP/outputmanager.h"
#include "CPP/pluginmanager.h"
#include "CPP/qmlmanager.h"
#include "CPP/buildmanager.h"
#include <iostream>



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
    QGuiApplication *app;


#if QT_VERSION >= QT_VERSION_CHECK(5, 8, 0)
    app = new QGuiApplication(argc, argv);
#else
    app = new QApplication(argc, argv);

#endif

    QCoreApplication::setOrganizationName("QuasarApp");
    QCoreApplication::setOrganizationDomain("https://quasarapp.github.io/QtDeployer/");
    QCoreApplication::setApplicationName("Qt-Deployer");

    app->setWindowIcon(QIcon("://icon"));

    QTranslator translator;

    QString locale = "";

    if(argc > 1) {
        locale = QString::fromLatin1(argv[1]);
    }

    if(!initLocale(locale, *app, translator)){
        std::cout << "error load language : " << locale.toStdString() <<std::endl;
    }

    CppManager C;
    QmlManager Q;
    PluginManager P;
    OutputManager O;
    BuildManager B;


    MainManager M(&C, &Q, &O, &P, &B);

#if QT_VERSION >= QT_VERSION_CHECK(5, 8, 0)
    QQmlApplicationEngine engine;

    auto *R = engine.rootContext();
    R->setContextProperty("CppManager", &C);
    R->setContextProperty("QmlManager", &Q);
    R->setContextProperty("PluginManager", &P);
    R->setContextProperty("MainManager", &M);
    R->setContextProperty("OutputManager", &O);
    R->setContextProperty("BuildManager", &B);



    engine.load(QUrl(QLatin1String("qrc:/QML/main.qml")));
    if (engine.rootObjects().isEmpty()) return -1;
#else
    MainWindow mainApp(&M);
    mainApp.show();
#endif

    return app->exec();

}
