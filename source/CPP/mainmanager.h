#ifndef MAINMANAGER_H
#define MAINMANAGER_H

#include "baseclass.h"
#include "cppmanager.h"
#include "outputmanager.h"
#include "pluginmanager.h"
#include "qmlmanager.h"
#include "buildmanager.h"

class MainManager : public BaseClass
{
	Q_OBJECT

	Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged)

	CppManager *m_cpp;
	QmlManager *m_qml;
	PluginManager *m_plg;
	OutputManager *m_out;
    BuildManager *m_bld;


	int m_state;

	QStringList getAllExecutables();

private slots:
    void buildFinished();

public:
	explicit MainManager(CppManager *cpp, QmlManager *qml, OutputManager *out,
                         PluginManager *plg, BuildManager* bld, QObject *parent = nullptr);

	int state() const;

public slots:
    void prepare(const QString &qtdir, const QString &projectdir, const QString &outdir);

	void start(bool erase);

	bool hasPrems(const QString &path);
	QString stringFromUrl(QString url);
	bool pathExists(bool isdir, const QString &path);

	void setState(int state);

signals:
	void stateChanged(int state);
};

#endif  // MAINMANAGER_H
