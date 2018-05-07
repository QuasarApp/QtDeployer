#include "baseclass.h"

QString BaseClass::m_qtdir = QString();
QString BaseClass::m_outputdir = QString();
QString BaseClass::m_projectdir = QString();
QString BaseClass::m_executablepath = QString();

QStringList BaseClass::findFilesInsideDir(const QString &name, const QString &dirpath)
{
	QStringList files;

	QDir dir(dirpath);
	dir.setNameFilters(QStringList(name));

	QDirIterator it(dir, QDirIterator::Subdirectories);
	while (it.hasNext()) files << it.next();

	return files;
}

BaseClass::BaseClass(QObject *parent) : QObject(parent) {}
