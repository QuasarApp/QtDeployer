#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "CPP/cppmanager.h"
#include "CPP/mainmanager.h"
#include "CPP/outputmanager.h"
#include "CPP/pluginmanager.h"
#include "CPP/qmlmanager.h"
#include "CPP/snapmanager.h"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	CppManager C;
	QmlManager Q;
	PluginManager P;
	OutputManager O;
    SnapManager S;

    MainManager M(&C, &Q, &O, &P, &S);

	QQmlApplicationEngine engine;

	auto *R = engine.rootContext();
	R->setContextProperty("CppManager", &C);
	R->setContextProperty("QmlManager", &Q);
	R->setContextProperty("PluginManager", &P);
	R->setContextProperty("MainManager", &M);
	R->setContextProperty("OutputManager", &O);
    R->setContextProperty("SnapManager", &S);


	engine.load(QUrl(QLatin1String("qrc:/QML/main.qml")));
	if (engine.rootObjects().isEmpty()) return -1;

	return app.exec();
}
