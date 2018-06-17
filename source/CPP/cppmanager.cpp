#include "cppmanager.h"

void CppManager::setQtLibraries(const QStringList &qtLibraries)
{
	if (m_qtLibraries == qtLibraries) return;

	m_qtLibraries = qtLibraries;
	emit qtLibrariesChanged(m_qtLibraries);
}

void CppManager::setCppLibraries(const QStringList &cppLibraries)
{
	if (m_cppLibraries == cppLibraries) return;

	m_cppLibraries = cppLibraries;
	emit cppLibrariesChanged(m_cppLibraries);
}

void CppManager::setNotFoundLibs(const QStringList &notFoundLibs)
{
	if (m_notFoundLibs == notFoundLibs) return;

	m_notFoundLibs = notFoundLibs;
	emit notFoundLibsChanged(m_notFoundLibs);
}

bool CppManager::isQtLib(const QString &lib) const{
    return lib.indexOf(m_qtdir) == 0 || lib.indexOf("libQt") > -1;
}

void CppManager::extractAllLibs(const QStringList &execfiles)
{
	for (const QString &execfile : execfiles)
		for (const QString &lib : extractLibsFromExecutable(execfile))
            if (!m_cppLibraries.contains(lib))
			{
				m_cppLibraries << lib;
				extractAllLibs(QStringList(lib));
			}
}

QStringList CppManager::extractLibsFromExecutable(const QString &execpath)
{
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("LD_LIBRARY_PATH", m_qtdir + "/lib");
    env.insert("QML_IMPORT_PATH", m_qtdir + "/qml");
    env.insert("QML2_IMPORT_PATH", m_qtdir + "/qml");
    env.insert("QT_PLUGIN_PATH", m_qtdir + "/plugins");
    env.insert("QT_QPA_PLATFORM_PLUGIN_PATH", m_qtdir + "/plugins/platforms");

	QProcess P;
    P.setProcessEnvironment(env);
	P.start("ldd " + execpath, QProcess::ReadOnly);

	if (!P.waitForStarted()) return QStringList();
	if (!P.waitForFinished()) return QStringList();

	auto data = QString(P.readAll());
	QStringList libs;

	for (QString &line : data.split("\n", QString::SkipEmptyParts))
	{
		line = line.simplified();
		auto innerlist = line.split(" ");

		if (innerlist.count() < 3) continue;
		line = innerlist[2];

		if (!line.startsWith("/"))
			m_notFoundLibs << innerlist[0];
		else
			libs << line;
	}

	return libs;
}

void CppManager::divideLibraries()
{
	for (const QString &lib : m_cppLibraries)
	{
		QString name;

        if (getName(name, lib) && !name.isEmpty() && isQtLib(lib))
		{
			m_qtLibraries << name;
			m_cppLibraries.removeOne(lib);
		}
	}
}

void CppManager::start(const QStringList &executables)
{
	m_qtLibraries.clear();
	m_cppLibraries.clear();
	m_notFoundLibs.clear();

	extractAllLibs(executables);
	divideLibraries();

	m_notFoundLibs.removeDuplicates();

    emit qtLibrariesChanged(m_qtLibraries);
    emit cppLibrariesChanged(m_cppLibraries);
    emit notFoundLibsChanged(m_notFoundLibs);
}

QStringList CppManager::getQtLibrariesFullPaths()
{
	QStringList paths;

	auto dir = m_qtdir + "/lib";
	for (const QString &qtlib : m_qtLibraries) paths << dir + "/" + qtlib;

	return paths;
}

CppManager::CppManager(QObject *parent) : BaseClass(parent) {}
QStringList CppManager::qtLibraries() const { return m_qtLibraries; }
QStringList CppManager::cppLibraries() const { return m_cppLibraries; }
QStringList CppManager::notFoundLibs() const { return m_notFoundLibs; }
