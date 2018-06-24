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

    Q_PROPERTY(QString log READ log NOTIFY logChanged)


	QStringList m_pathsToCopy;
	QList<bool> m_copySuccess;
    QProcess installer_process;
    QString tempLog;


	bool copyDir(const QString &source, const QString &destin);
	bool copyFile(const QString &source, const QString &destin);

	void copyCpp(const QStringList &libs);
	void copyQml(const QStringList &dirs);
	void copyPlugins(const QStringList &plugins);

    bool isInstallFW() const;

    void checkInstallFrameWork();

	void createDirectories();
	void createRunFile();
    void createEntryScript();
    bool createIcon();
    void createInstaller();
    bool createModule(const QString& from, const QString& to, const QStringList& params);
	void copyExec();

private slots:
    void buildLog();
    void buildFunished(int, QProcess::ExitStatus exitStatus);

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
    const QString& log() const;

signals:
	void pathsToCopyChanged(QStringList pathsToCopy);
	void copySuccessChanged(QList<bool> copySuccess);
    void finished();
    void logChanged(QString);


};

#endif  // OUTPUTMANAGER_H
