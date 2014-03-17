#ifndef FILE_H
#define FILE_H

#include <QList>
#include <QFile>
#include <QStringList>
#include <QRegExp>
#include <QDebug>
#include "iniitem.h"

/*
 * Będzie to klasa która będzie reprezętowała plik z /elements oraz jego zawartość
 * Zachowywała kolejność elementów
 */
class IniFile
{
private:
	QString			c_path;
	IniParam		c_offset;
	QStringList		c_lines;
	QList<QString>	c_names;
	QList<IniItem>	c_items;
public:
	IniFile();
	IniFile(const QString &path);

	bool	load(const QString &in); // load data from the file
	bool	save(); // save data to the file

	bool		isComment(const QString &line);
	QList<IniItem*> getAll();

	bool		isEmpty()							{ return c_items.isEmpty(); }
	bool		contains(const QString &name);
	int			count()								{ return c_names.count(); }
	int			indexOf(const QString &name)		{ return c_names.indexOf(name); }
	IniItem&	item(int i)							{ return c_items[i]; }
	IniItem&	item(const QString &name)			{ return c_items[indexOf(name)]; }
	IniItem&	operator[](int i)					{ return item(i); }
	IniItem&	operator[](const QString &name)		{ return item(name); }
};

#endif // FILE_H
