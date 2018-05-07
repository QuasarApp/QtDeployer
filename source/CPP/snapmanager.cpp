#include "snapmanager.h"

bool SnapManager::checkSnapDirs()const{
    QDir dir(m_projectdir);

    if(!dir.cd("snap")){
        return false;
    }

    if(dir.entryList(QStringList() << "*.desktop" << "snapcraft.yaml").length() < 2){
        return false;
    }
    return true;
}

bool copyRecursively(const QString &srcFilePath,
                            const QString &tgtFilePath)
{
    QFileInfo srcFileInfo(srcFilePath);
    if (srcFileInfo.isDir()) {

        QDir targetDir(tgtFilePath);
        targetDir.cdUp();

        if (!targetDir.mkdir(QFileInfo(tgtFilePath).fileName()))
            return false;

        QDir sourceDir(srcFilePath);
        QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);

        foreach (const QString &fileName, fileNames) {
            const QString newSrcFilePath
                    = srcFilePath + QLatin1Char('/') + fileName;

            const QString newTgtFilePath
                    = tgtFilePath + QLatin1Char('/') + fileName;

            if (!copyRecursively(newSrcFilePath, newTgtFilePath))
                return false;
        }
    } else {

        if (!QFile::copy(srcFilePath, tgtFilePath))
            return false;
    }

    return true;
}

bool SnapManager::copySnap()const {
    return copyRecursively(m_projectdir + "/snap", m_outputdir);
}

void SnapManager::start()
{
    if(!copySnap()){
        emit fail(tr("copy snapcraft error!"));
        return;
    }

    if(!checkSnapDirs()){
        emit fail(tr("create a snapcraft.yaml and desktop file!"));
    } else {
        QProcess P;
        P.setArguments(QStringList() << "snapcraft");
        P.start("gnome-terminal", QProcess::ReadOnly);

        if (!P.waitForStarted() || !P.waitForFinished()){
            emit fail(tr("gnome-terminal not found, if you need a create snap package."
                         "you need call \'snapcraft\' in final build directory"));
            return;
        }
    }
}

SnapManager::SnapManager(QObject *parent) : BaseClass(parent) {}
