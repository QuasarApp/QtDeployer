#ifndef BUILDMANAGER_H
#define BUILDMANAGER_H

#include "baseclass.h"

class BuildManager : public BaseClass
{
    Q_OBJECT
private:
    QString qmake;
    QString tempBuildFolder;
    bool initFolderName();
    bool initQMake();


public:
    explicit BuildManager(QObject *parent = nullptr);
    bool build();

signals:

public slots:
};

#endif // BUILDMANAGER_H
