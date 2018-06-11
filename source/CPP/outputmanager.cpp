#include "outputmanager.h"

void OutputManager::setPathsToCopy(const QStringList &pathsToCopy)
{
	if (m_pathsToCopy == pathsToCopy) return;

	m_pathsToCopy = pathsToCopy;
	emit pathsToCopyChanged(m_pathsToCopy);
}

void OutputManager::setCopySuccess(const QList<bool> &copySuccess)
{
	if (m_copySuccess == copySuccess) return;

	m_copySuccess = copySuccess;
	emit copySuccessChanged(m_copySuccess);
}

bool OutputManager::copyDir(const QString &source, const QString &destin)
{
	QDir().mkpath(destin);

	QProcess P;
	P.start(QString("cp -a %1/. %2/").arg(source, destin));

	P.waitForStarted(1000);
	P.waitForFinished();

	return P.exitStatus() == QProcess::NormalExit;
}

void OutputManager::copyCpp(const QStringList &libs)
{
    auto libdir = m_outputdir + "/lib/data/lib/";

	for (const QString &S : libs)
	{
		auto path = libdir + "/" + QFileInfo(S).fileName();
		m_pathsToCopy << path;
		m_copySuccess << copyFile(S, path);
	}
}

void OutputManager::copyAll(const QStringList &qtlibs, const QStringList &libs,
							const QStringList &dirs, const QStringList &plugins,
							bool erase)
{
	m_pathsToCopy.clear();
	m_copySuccess.clear();

	if (erase)
	{
		QDir(m_outputdir).removeRecursively();
		QDir dir(m_outputdir);
		dir.cdUp();
		dir.mkdir(QDir(m_outputdir).dirName());
	}

	createDirectories();

	if (libs.count() != 0) copyCpp(libs);
	copyCpp(qtlibs);
	copyQml(dirs);
	copyPlugins(plugins);
	copyExec();
	createRunFile();

	emit pathsToCopyChanged(m_pathsToCopy);
	emit copySuccessChanged(m_copySuccess);
}

void OutputManager::copyQml(const QStringList &dirs)
{
    auto qmldir = m_outputdir + "/qml/data/qml/";

	for (const QString &S : dirs)
	{
		QString path = qmldir + "/" + S;
		m_pathsToCopy << path + "/";
		m_copySuccess << copyDir(m_qtdir + "/qml/" + S, path);
	}
}

void OutputManager::copyPlugins(const QStringList &plugins)
{
	QString qtpath = m_qtdir + "/plugins/";
    QString path = m_outputdir + "/plugins/data/plugins";

	for (const QString &plugin : plugins)
	{
		m_pathsToCopy << path + plugin + "/";
		m_copySuccess << copyDir(qtpath + plugin, path + plugin);
	}
}

void OutputManager::copyExec()
{
    auto path = m_outputdir + "/base/data/bin" + QFileInfo(m_executablepath).fileName();

	m_pathsToCopy << path;
	m_copySuccess << copyFile(m_executablepath, path);
}

void OutputManager::createRunFile()
{
	QString content =
		"#!/bin/sh\n"
		"export LD_LIBRARY_PATH=`pwd`/lib\n"
		"export QML_IMPORT_PATH=`pwd`/qml\n"
		"export QML2_IMPORT_PATH=`pwd`/qml\n"
		"export QT_PLUGIN_PATH=`pwd`/plugins\n"
		"export QT_QPA_PLATFORM_PLUGIN_PATH=`pwd`/plugins/platforms\n"
		"./bin/%1";

	content = content.arg(QFileInfo(m_executablepath).completeBaseName());

    QString fname = m_outputdir + "/base/" + QDir::separator() +
					QFileInfo(m_executablepath).completeBaseName() + ".sh";

	QFile F(fname);
	m_pathsToCopy << fname;
	m_copySuccess << F.open(QIODevice::WriteOnly);

	F.write(content.toUtf8());
	F.flush();
	F.close();

	F.setPermissions(QFileDevice::ExeUser | QFileDevice::WriteUser |
					 QFileDevice::ReadUser);
}

void OutputManager::createDirectories()
{
	m_pathsToCopy << m_outputdir + "/bin/";
	m_copySuccess << QDir(m_outputdir).mkdir("bin");

	m_pathsToCopy << m_outputdir + "/qml/";
	m_copySuccess << QDir(m_outputdir).mkdir("qml");

	m_pathsToCopy << m_outputdir + "/lib/";
	m_copySuccess << QDir(m_outputdir).mkdir("lib");

	m_pathsToCopy << m_outputdir + "/plugins/";
	m_copySuccess << QDir(m_outputdir).mkdir("plugins");
}

bool OutputManager::copyFile(const QString &source, const QString &destin)
{
	return QFile::copy(source, destin);
}

OutputManager::OutputManager(QObject *parent) : BaseClass(parent) {}
QStringList OutputManager::pathsToCopy() const { return m_pathsToCopy; }
QList<bool> OutputManager::copySuccess() const { return m_copySuccess; }
