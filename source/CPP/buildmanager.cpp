#include "buildmanager.h"
#include <QProcess>

BuildManager::BuildManager(QObject *parent) : BaseClass(parent)
{

}

bool BuildManager::initQMake() {

    QDir dir(m_qtdir);

    if(!dir.exists("/bin/qmake")){
        return false;
    }

    qmake = m_qtdir + "/bin/qmake";
    return true;

}

bool BuildManager::initFolderName() {
    QDir dir(m_projectdir);
    if(!dir.cd("..")) {
        return false;
    }

    QFileInfoList filesList = dir.entryInfoList(".pro");

    if(filesList.size() < 1){
        return false;
    }
    
    QString projectName = filesList.first().baseName();

    tempBuildFolder = dir.absolutePath() + "/Build-" + projectName;
    if(!dir.exists(tempBuildFolder) && !dir.mkdir(tempBuildFolder)){
        tempBuildFolder.clear();
        return false;
    }

    return true;
}

bool BuildManager::build(){
    if(initQMake() && initFolderName()){
        return false;
    }


    QProcess pQMake;

    pQMake.setProgram(qmake);

    pQMake.setArguments(QStringList() << );

}

