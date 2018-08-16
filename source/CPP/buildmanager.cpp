#include "buildmanager.h"
#include <QProcess>
#include <QThread>

BuildManager::BuildManager(QObject *parent) : BaseClass(parent)
{
    connect(&pQMake, &QProcess::readyRead, this, &BuildManager::buildLog);
    connect(&pQMake, SIGNAL(finished(int)), this, SLOT(buildFinihed(int)));

}

void BuildManager::buildLog(){
    tempLog = pQMake.readAll();
    emit logChanged(tempLog);
}

void BuildManager::buildFinihed(int error) {
    if(pQMake.program() == "make" && !error){
        m_executablepath = tempBuildFolder + "/" + projectName;
        emit finished();
    }
}

bool BuildManager::initQMake() {

    QDir dir(m_qtdir);

    if(!dir.exists("bin/qmake")){
        return false;
    }

    qmake = m_qtdir + "/bin/qmake";
    return true;

}

const QString& BuildManager::log() const{
    return tempLog;
}

bool BuildManager::createFulder(QDir& dir, QString &path, const QString &name) const{

    path = dir.absolutePath() + "/" + name;
    if(dir.exists(path) && !QDir(path).removeRecursively()){

        path.clear();
        return false;
    }

    if(!dir.mkdir(path)){
        path.clear();
        return false;
    }

    return true;
}

bool BuildManager::initFolders() {

    QFileInfo pro(m_projectfile);
    QDir dir = pro.absoluteDir();
    if(!dir.cd("..")) {
        return false;
    }

    QFile f(m_projectfile);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)){
        return false;
    }

    QString proFile = f.readAll();
    f.close();

    proFile.replace(" ", "");
    int tempIndex = proFile.indexOf(QRegExp("TARGET=") );
    if(tempIndex < 0) {

        projectName = pro.baseName();
    } else {
        int beginTarget = tempIndex + 7;

        tempIndex = proFile.indexOf("\n", beginTarget);
        int longTraget = -1;

        if(tempIndex >= 0){
            longTraget = tempIndex - beginTarget;
        }
        projectName = proFile.mid(beginTarget, longTraget);
    }


    if(!createFulder(dir, tempBuildFolder, "Build-" + projectName)){
        return false;
    }

    if(!createFulder(dir, m_outputdir, "Release-" + projectName)){
        return false;
    }

    return true;
}

bool BuildManager::build(){
    if(!initQMake()){
        emit logChanged(tr("init QMake error!"));
        return false;
    }

    if(!initFolders()){
        emit logChanged(tr("init Folders error!"));
        return false;
    }

    pQMake.setProgram(qmake);
    pQMake.setWorkingDirectory(tempBuildFolder);
    pQMake.setArguments(QStringList() <<  m_projectfile);

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("LD_LIBRARY_PATH", m_qtdir + "/lib");
    env.insert("QML_IMPORT_PATH", m_qtdir + "/qml");
    env.insert("QML2_IMPORT_PATH", m_qtdir + "/qml");
    env.insert("QT_PLUGIN_PATH", m_qtdir + "/plugins");
    env.insert("QT_QPA_PLATFORM_PLUGIN_PATH", m_qtdir + "/plugins/platforms");

    pQMake.setProcessEnvironment(env);

    pQMake.start();

    if(!pQMake.waitForFinished()){
        emit logChanged(tr("run qmake error!"));
        return false;
    }

    pQMake.setProgram("make");

    pQMake.setArguments(QStringList() << QString("-j%0").arg(QThread::idealThreadCount()));
    pQMake.start();

    return true;

}

