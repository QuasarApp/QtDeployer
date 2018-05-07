#include "mainmanager.h"

QStringList MainManager::getAllExecutables()
{
	QStringList list = m_qml->getAllSoFiles();
	list << m_plg->getAllSoFiles();
	list << m_executablepath;

	return list;
}

MainManager::MainManager(CppManager *cpp, QmlManager *qml, OutputManager *out,
                         PluginManager *plg, SnapManager *snp, QObject *parent)
	: BaseClass(parent)
{
	setState(0);

	m_cpp = cpp;
	m_qml = qml;
	m_out = out;
	m_plg = plg;
    m_snp = snp;

}

void MainManager::prepare(const QString &qtdir, const QString &execpath,
						  const QString &projectdir, const QString &outdir)
{
	QStringList list;
	list << qtdir << execpath << projectdir << outdir;

	for (QString &S : list)
		if (S[S.count() - 1] == "/") S.remove(S.count() - 1, 1);

	m_qtdir = list[0];
	m_executablepath = list[1];
	m_projectdir = list[2];
	m_outputdir = list[3];

	m_qml->start();
	m_plg->start();
	m_cpp->start(getAllExecutables());
}

void MainManager::start(bool erase)
{
	setState(1);

	m_out->copyAll(m_cpp->getQtLibrariesFullPaths(), m_cpp->cppLibraries(),
				   m_qml->foundImports(), m_plg->neededPlugins(), erase);

	setState(2);
}

bool MainManager::hasPrems(const QString &path)
{
	QFileInfo info(path);
	return (info.isReadable() && info.isWritable());
}

QString MainManager::stringFromUrl(QString url)
{
	return url.remove("file://");
}

bool MainManager::pathExists(bool isdir, const QString &path)
{
	if (isdir) return QDir(path).exists();
	return QFile(path).exists();
}

void MainManager::setState(int state)
{
	if (m_state == state) return;

	m_state = state;
	emit stateChanged(m_state);
}

int MainManager::state() const { return m_state; }
