#if QT_VERSION > 0x050501
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



bool loadTr(QGuiApplication *app){
    QTranslator translator;

    QString defaultLocale = QLocale::system().name();
    defaultLocale.truncate(defaultLocale.lastIndexOf('_'));

    if(!translator.load(QString(":/languages/%0").arg(defaultLocale))){
        return false;
    }
    app->installTranslator(&translator);

    return true;

}

int main(int argc, char *argv[])
{
    QGuiApplication *app;;


#if QT_VERSION > 0x050501
    app = new QGuiApplication(argc, argv);
#else
    app = new QApplication(argc, argv);

#endif


    app->setWindowIcon(QIcon("://icon"));

    loadTr(app);

    CppManager C;
    QmlManager Q;
    PluginManager P;
    OutputManager O;
    BuildManager B;


    MainManager M(&C, &Q, &O, &P, &B);

#if QT_VERSION > 0x050501
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


    int returnCode = app->exec();
    delete app;
    return  returnCode;

}
