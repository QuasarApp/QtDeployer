#ifndef SNAPMANAGER_H
#define SNAPMANAGER_H

#include "baseclass.h"

class SnapManager : public BaseClass
{
	Q_OBJECT

    bool checkSnapDirs()const;

    bool copySnap()const;

public:
    explicit SnapManager(QObject *parent = nullptr);

public slots:
    void start();


signals:
    void done(QString snap);
    void fail(QString error);
};

#endif  // CPPMANAGER_H
