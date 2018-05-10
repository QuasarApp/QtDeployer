#ifndef CPPMANAGER_H
#define CPPMANAGER_H

#include "baseclass.h"

class CppManager : public BaseClass
{
	Q_OBJECT
	Q_PROPERTY(QStringList qtLibraries READ qtLibraries WRITE setQtLibraries
				   NOTIFY qtLibrariesChanged)

	Q_PROPERTY(QStringList cppLibraries READ cppLibraries WRITE setCppLibraries
				   NOTIFY cppLibrariesChanged)

	Q_PROPERTY(QStringList notFoundLibs READ notFoundLibs WRITE setNotFoundLibs
				   NOTIFY notFoundLibsChanged)

	QStringList m_qtLibraries;
	QStringList m_cppLibraries;
	QStringList m_notFoundLibs;

    bool isQtLib(const QString&) const;

public:  // TODO remove this line
	void extractAllLibs(const QStringList &execfiles);
	QStringList extractLibsFromExecutable(const QString &execpath);

	void divideLibraries();

public:
	explicit CppManager(QObject *parent = nullptr);

	QStringList qtLibraries() const;
	QStringList cppLibraries() const;
	QStringList notFoundLibs() const;

	QStringList getQtLibrariesFullPaths();

	void start(const QStringList &executables);

public slots:
	void setQtLibraries(const QStringList &qtLibraries);
	void setCppLibraries(const QStringList &cppLibraries);
	void setNotFoundLibs(const QStringList &notFoundLibs);

signals:
	void qtLibrariesChanged(QStringList qtLibraries);
	void cppLibrariesChanged(QStringList cppLibraries);
	void notFoundLibsChanged(QStringList notFoundLibs);
};

#endif  // CPPMANAGER_H
