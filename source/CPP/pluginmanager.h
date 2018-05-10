#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "baseclass.h"

class PluginManager : public BaseClass
{
	Q_OBJECT

	Q_PROPERTY(QStringList neededPlugins READ neededPlugins WRITE
				   setNeededPlugins NOTIFY neededPluginsChanged)

	QStringList m_neededPlugins;

	QStringList extractModules();
	QStringList findPluginsFromModules();
	QStringList extractMudoulesFromFile(const QString &filepath);

public:
	explicit PluginManager(QObject *parent = nullptr);

	QStringList neededPlugins() const;

	void start();
	QStringList getAllSoFiles();

public slots:
	void setNeededPlugins(const QStringList &neededPlugins);

signals:
	void neededPluginsChanged(QStringList neededPlugins);
};

#endif  // PLUGINMANAGER_H
