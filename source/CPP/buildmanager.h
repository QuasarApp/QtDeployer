#ifndef BUILDMANAGER_H
#define BUILDMANAGER_H

#include "baseclass.h"

class BuildManager : public BaseClass
{
    Q_OBJECT
    Q_PROPERTY(QString log READ log NOTIFY logChanged)

private:
    QString qmake;
    QString tempBuildFolder;
    QString tempLog;
    QString projectName;
    QProcess pQMake;

    bool createFulder(QDir& dir, QString& path, const QString& name) const;
    bool initFolders();
    bool initQMake();

private slots:
    void buildLog();
    void buildFinihed(int error);

public:
    explicit BuildManager(QObject *parent = nullptr);
    bool build();

signals:
    void logChanged();
    void finished();

public slots:
    const QString& log() const;
};

#endif // BUILDMANAGER_H
