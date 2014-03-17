#ifndef LISTFILE_H
#define LISTFILE_H

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QStringList>
#include <QList>
#include <QDebug>
#include <QRegExp>
#include "inifile.h"

class ListFile
{
private:
	QString c_path;
	QList<IniFile> c_files;

	bool load();

public:
	ListFile(const QString &pathIn);
	~ListFile();

	bool			save();
	int				count()						{return c_files.count();}
	IniFile*		operator[](int i);
	QList<IniItem*> getAll();
};

#endif // LISTFILE_H
