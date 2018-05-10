#ifndef QMLMANAGER_H
#define QMLMANAGER_H

#include "baseclass.h"

class QmlManager : public BaseClass
{
	Q_OBJECT

	Q_PROPERTY(QStringList foundImports READ foundImports WRITE setFoundImports
				   NOTIFY foundImportsChanged)

	Q_PROPERTY(QStringList notFoundImports READ notFoundImports WRITE
				   setNotFoundImports NOTIFY notFoundImportsChanged)

	QStringList m_foundImports;
	QStringList m_notFoundImports;

	QStringList m_secondVersionImports;

public:  // TODO remove
	void extractImportsFromDir(const QString &dirpath);
	QStringList extractImportsFromFile(const QString &filepath);

	QStringList getAllQtQmlImports();
	void removeInnerImports();
	void divideFoundAndNotFound();

public:
	explicit QmlManager(QObject *parent = nullptr);

	QStringList foundImports() const;
	QStringList notFoundImports() const;

	void start();
	QStringList getAllSoFiles();

public slots:
	void setFoundImports(const QStringList &foundImports);
	void setNotFoundImports(const QStringList &notFoundImports);

signals:
	void foundImportsChanged(QStringList foundImports);
	void notFoundImportsChanged(QStringList notFoundImports);
};

#endif  // QMLMANAGER_H
