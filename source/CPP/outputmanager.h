#ifndef OUTPUTMANAGER_H
#define OUTPUTMANAGER_H

#include "baseclass.h"

class OutputManager : public BaseClass
{
	Q_OBJECT

	Q_PROPERTY(QStringList pathsToCopy READ pathsToCopy WRITE setPathsToCopy
				   NOTIFY pathsToCopyChanged)

	Q_PROPERTY(QList<bool> copySuccess READ copySuccess WRITE setCopySuccess
				   NOTIFY copySuccessChanged)

	QStringList m_pathsToCopy;
	QList<bool> m_copySuccess;

	bool copyDir(const QString &source, const QString &destin);
	bool copyFile(const QString &source, const QString &destin);

	void copyCpp(const QStringList &libs);
	void copyQml(const QStringList &dirs);
	void copyPlugins(const QStringList &plugins);

    bool isInstallFW() const;

    void checkInstallFrameWork();

	void createDirectories();
	void createRunFile();
    void createInstaller();
    bool createModule(const QString& from, const QString& to, const QStringList& params);
	void copyExec();

public:
	explicit OutputManager(QObject *parent = nullptr);

	QStringList pathsToCopy() const;
	QList<bool> copySuccess() const;

	void copyAll(const QStringList &qtlibs, const QStringList &libs,
				 const QStringList &dirs, const QStringList &plugins,
				 bool erase);

public slots:
	void setPathsToCopy(const QStringList &pathsToCopy);
	void setCopySuccess(const QList<bool> &copySuccess);

signals:
	void pathsToCopyChanged(QStringList pathsToCopy);
	void copySuccessChanged(QList<bool> copySuccess);
};

#endif  // OUTPUTMANAGER_H
