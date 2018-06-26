#include "outputmanager.h"
#include "utils.h"
#include <QDate>

OutputManager::OutputManager(QObject *parent) : BaseClass(parent) {/*finished*/
    connect(&installer_process, &QProcess::readyReadStandardOutput, this, &OutputManager::buildLog);
//    connect(&installer_process, &QProcess::finished, this, &OutputManager::buildFunished);
    connect(&installer_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(buildFunished(int, QProcess::ExitStatus)));
}

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

const QString& OutputManager::log() const{
    return tempLog;
}

void OutputManager::buildLog(){
    tempLog = installer_process.readAll();
    emit logChanged(tempLog);
}

void OutputManager::buildFunished(int error, QProcess::ExitStatus){
    if(!error){
        emit finished();
    }
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

    QString temp = "/lib";
    if(isInstallFW()){
        temp = "/packages/lib/data/lib";
    }

    auto libdir = m_outputdir + temp;

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

    tempLog = tr("Start preparing project");
    emit logChanged(tempLog);

	if (erase)
	{

        tempLog = tr("Start erase output dir");
        emit logChanged(tempLog);

		QDir(m_outputdir).removeRecursively();
		QDir dir(m_outputdir);
		dir.cdUp();
		dir.mkdir(QDir(m_outputdir).dirName());
	}

    checkInstallFrameWork();

	createDirectories();

    if (libs.count() != 0){
        tempLog = tr("Copy c++ libs");
        emit logChanged(tempLog);
        copyCpp(libs);
    }
    tempLog = tr("Copy c++/qt libs");
    emit logChanged(tempLog);
	copyCpp(qtlibs);

    tempLog = tr("Copy qml libs");
    emit logChanged(tempLog);
	copyQml(dirs);

    tempLog = tr("Copy Plugins");
    emit logChanged(tempLog);
	copyPlugins(plugins);

    tempLog = tr("Copy Execute files");
    emit logChanged(tempLog);
	copyExec();

	createRunFile();

    if(isInstallFW())
        createInstaller();

	emit pathsToCopyChanged(m_pathsToCopy);
	emit copySuccessChanged(m_copySuccess);
}

void OutputManager::copyQml(const QStringList &dirs)
{
    QString temp = "/qml";
    if(isInstallFW()){
        temp = "/packages/qml/data/qml";
    }


    auto qmldir = m_outputdir + temp;

	for (const QString &S : dirs)
	{
		QString path = qmldir + "/" + S;
		m_pathsToCopy << path + "/";
		m_copySuccess << copyDir(m_qtdir + "/qml/" + S, path);
	}
}

bool OutputManager::isInstallFW() const {
    return !m_binarycreator.isEmpty();
}

void OutputManager::checkInstallFrameWork(){

    tempLog = tr("check InstallFrameWork");
    emit logChanged(tempLog);

    QDir dir(m_qtdir);
    if(!dir.cd("../../Tools/QtInstallerFramework")){
        m_binarycreator = QString();
        return;
    }

    QStringList list = dir.entryList();

    int index_of_max = 0;
    double maxVersion = 0;
    for(int i = 0; i < list.size(); i++){
        if(list.at(i).toDouble() > maxVersion){
            index_of_max = i;
            maxVersion = list.at(i).toDouble();
        }
    }

    if(!maxVersion || !index_of_max){
        m_binarycreator = QString();
        return;
    }

    if(!dir.cd(list[index_of_max])){
        m_binarycreator = QString();
        return;
    }

    m_binarycreator = dir.absolutePath() + "/bin/binarycreator";


    if(!QFile::exists(m_binarycreator)){
        m_binarycreator = QString();
        tempLog = tr("InstallFrameWork not findet");
        emit logChanged(tempLog);

        return;
    }

    tempLog = tr("InstallFrameWork findet in %0").arg(m_binarycreator);
    emit logChanged(tempLog);

}

void OutputManager::copyPlugins(const QStringList &plugins)
{
    QString temp = "/plugins/";
    if(isInstallFW()){
        temp = "/packages/plugins/data/plugins/";
    }

	QString qtpath = m_qtdir + "/plugins/";
    QString path = m_outputdir + temp;

	for (const QString &plugin : plugins)
	{
		m_pathsToCopy << path + plugin + "/";
		m_copySuccess << copyDir(qtpath + plugin, path + plugin);
	}
}

void OutputManager::copyExec()
{
    QString temp = "/bin/";
    if(isInstallFW()){
        temp = "/packages/base/data/bin/";
    }

    auto path = m_outputdir + temp + QFileInfo(m_executablepath).fileName();

	m_pathsToCopy << path;
	m_copySuccess << copyFile(m_executablepath, path);
}

bool OutputManager::createIcon(){
    QFile f(appIcon);
    QByteArray icon;

    if(!f.open(QIODevice::ReadOnly)){
        return false;
    }
    icon = f.readAll();
    f.close();

    QString name = QFileInfo(appIcon).fileName();
    f.setFileName(m_outputdir + "/packages/base/data/" + name);

    if(!f.open(QIODevice::WriteOnly)){
        return false;
    }
    f.write(icon.data(), icon.size());

    f.close();

    f.setFileName(m_outputdir + "/config/" + name);
    if(!f.open(QIODevice::WriteOnly)){
        return false;
    }
    f.write(icon.data(), icon.size());

    f.close();

    appIcon = name;

    return true;
}

void OutputManager::createEntryScript(){
    QString temp = "";
    if(isInstallFW()){
        temp = "/packages/base/data";
    }

    QFile f(":/install/InstallTemplate/CreateDesktopEntry.sh");
    f.open(QIODevice::ReadOnly);

    QString content = f.readAll();

    QString fname = m_outputdir + temp + QDir::separator() +
                    "CreateDesktopEntry.sh";

    QFile F(fname);
    m_pathsToCopy << fname;
    m_copySuccess << F.open(QIODevice::WriteOnly);

    F.write(content.toUtf8());
    F.flush();
    F.close();

    F.setPermissions(QFileDevice::ExeUser | QFileDevice::WriteUser |
                     QFileDevice::ReadUser);
}

void OutputManager::createRunFile()
{

    QString temp = "";
    if(isInstallFW()){
        temp = "/packages/base/data";
    }

	QString content =
		"#!/bin/sh\n"
		"export LD_LIBRARY_PATH=`pwd`/lib\n"
		"export QML_IMPORT_PATH=`pwd`/qml\n"
		"export QML2_IMPORT_PATH=`pwd`/qml\n"
		"export QT_PLUGIN_PATH=`pwd`/plugins\n"
		"export QT_QPA_PLATFORM_PLUGIN_PATH=`pwd`/plugins/platforms\n"
		"./bin/%1";

	content = content.arg(QFileInfo(m_executablepath).completeBaseName());

    QString fname = m_outputdir + temp + QDir::separator() +
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

bool OutputManager::createModule(const QString &from, const QString &to, const QStringList &params){
    QFile tempFile;
    tempFile.setFileName(from);

    if(!tempFile.open(QIODevice::ReadOnly)){
        return false;
    }

    QString text = tempFile.readAll();
    tempFile.close();

    for(QString i : params){
        text = text.arg(i);
    }

    tempFile.setFileName(to);

    if(!tempFile.open(QIODevice::ReadWrite) &&
       QDir().mkpath(QFileInfo(to).absolutePath()) &&
       !tempFile.open(QIODevice::ReadWrite)){
        return false;
    }

    tempFile.write(text.toLatin1());
    tempFile.close();

    return true;
}

void OutputManager::createInstaller(){

    tempLog = tr("create installer");
    emit logChanged(tempLog);

    if(!createIcon()){
        tempLog = tr("create icon fail!");
        emit logChanged(tempLog);
        return;
    }

    createModule(":/install/InstallTemplate/config.xml",
                 m_outputdir + "/config/config.xml",
                 QStringList() << projectName <<
                 Utils::getVersion() <<
                 Utils::getPublicher() <<
                 "QtDeployer" <<
                 QDate::currentDate().toString("yyyy-MM-dd") <<
                 appIcon);


    createModule(":/install/InstallTemplate/controlScript.js",
                 m_outputdir + "/config/controlScript.js",
                 QStringList() << appIcon);


    createModule(":/install/InstallTemplate/package.xml",
                 m_outputdir + "/packages/base/meta/package.xml",
                 QStringList() << "base" <<
                 "base data of " + projectName  <<
                 Utils::getVersion() <<
                 QDate::currentDate().toString("yyyy-MM-dd") <<
                 "true" <<
                 "");


    createModule(":/install/InstallTemplate/package.xml",
                 m_outputdir + "/packages/qml/meta/package.xml",
                 QStringList() << "qml" <<
                 "qml data of "  + projectName  <<
                 Utils::getVersion() <<
                 QDate::currentDate().toString("yyyy-MM-dd") <<
                 "true" <<
                 "");

    createModule(":/install/InstallTemplate/package.xml",
                 m_outputdir + "/packages/lib/meta/package.xml",
                 QStringList() << "lib" <<
                 "lib data of " + projectName  <<
                 Utils::getVersion() <<
                 QDate::currentDate().toString("yyyy-MM-dd") <<
                 "true" <<
                 "");

    createModule(":/install/InstallTemplate/package.xml",
                 m_outputdir + "/packages/plugins/meta/package.xml",
                 QStringList() << "plugins" <<
                 "plugins data of " + projectName  <<
                 Utils::getVersion() <<
                 QDate::currentDate().toString("yyyy-MM-dd") <<
                 "true" <<
                 "");

    installer_process.setProgram(m_binarycreator);
    /*
-c $$PWD/config/config.xml -p $$PWD/packages ${QMAKE_FILE_OUT}*/
    installer_process.setArguments(QStringList() << "-c" <<
                               m_outputdir + "/config/config.xml" <<
                               "-p" <<
                               m_outputdir + "/packages" <<
                               m_outputdir + "/installer_" + projectName <<
                               "-v");

    installer_process.start();

}

void OutputManager::createDirectories()
{

    tempLog = tr("Create Directories");
    emit logChanged(tempLog);

    if(isInstallFW()){
        m_pathsToCopy << m_outputdir + "/config";
        m_copySuccess << QDir(m_outputdir).mkpath("config");

        m_pathsToCopy << m_outputdir + "/packages/base/data/bin";
        m_copySuccess << QDir(m_outputdir).mkpath("packages/base/data/bin");

        m_pathsToCopy << m_outputdir + "/packages/qml/data/qml";
        m_copySuccess << QDir(m_outputdir).mkpath("packages/qml/data/qml");

        m_pathsToCopy << m_outputdir + "/packages/lib/data/lib/";
        m_copySuccess << QDir(m_outputdir).mkpath("packages/lib/data/lib");

        m_pathsToCopy << m_outputdir + "/packages/plugins/data/plugins";
        m_copySuccess << QDir(m_outputdir).mkpath("packages/plugins/data/plugins");

    } else {
        m_pathsToCopy << m_outputdir + "/bin/";
        m_copySuccess << QDir(m_outputdir).mkdir("bin");

        m_pathsToCopy << m_outputdir + "/qml/";
        m_copySuccess << QDir(m_outputdir).mkdir("qml");

        m_pathsToCopy << m_outputdir + "/lib/";
        m_copySuccess << QDir(m_outputdir).mkdir("lib");

        m_pathsToCopy << m_outputdir + "/plugins/";
        m_copySuccess << QDir(m_outputdir).mkdir("plugins");
    }
}

bool OutputManager::copyFile(const QString &source, const QString &destin)
{
	return QFile::copy(source, destin);
}

QStringList OutputManager::pathsToCopy() const { return m_pathsToCopy; }
QList<bool> OutputManager::copySuccess() const { return m_copySuccess; }
