#include "baseclass.h"
#include <QRegularExpression>

QString BaseClass::m_qtdir = QString();
QString BaseClass::m_outputdir = QString();
QString BaseClass::m_projectfile = QString();
QString BaseClass::m_executablepath = QString();
QString BaseClass::m_binarycreator = QString();
QString BaseClass::projectName = QString();
QString BaseClass::appIcon = QString();

QStringList BaseClass::findFilesInsideDir(const QString &name, const QString &dirpath)
{
	QStringList files;

	QDir dir(dirpath);
	dir.setNameFilters(QStringList(name));

	QDirIterator it(dir, QDirIterator::Subdirectories);
	while (it.hasNext()) files << it.next();

	return files;
}

bool BaseClass::getName(QString &name, const QString &url) const{

    int index = url.lastIndexOf(QRegularExpression("[\\\/]"));

    if(index < 0 || url.isEmpty()){
        return false;
    }

    index = url.length() - index - 1;

    name = url.right(index);
    return true;
}

BaseClass::BaseClass(QObject *parent) : QObject(parent) {}
