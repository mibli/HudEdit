#ifndef INIITEM_H
#define INIITEM_H

#include <QDebug>
#include <QHash>
#include <QStringList>
#include <QRect>
#include <QPointF>
#include <QPair>
#include <QDataStream>
#include "iniparam.h"

class IniItem
{
public:
private:
	QStringList			c_labels;
	QList<IniParam*>	c_values;
public:
	IniItem();
	IniItem(const QString &line)					{ insert(line); }
	IniItem(const QStringList &lines)				{ load(lines); }

	bool insert(const QString &line);
	bool load(const QStringList &lines);
	QString line(int i) const						{ return c_labels[i] + ": " + *c_values[i]; }
	QStringList	lines() const;
	QString toString()								{ return lines().join("\n"); }

	bool lin2par(const QString &in, QString &label, QString &value);
	bool lin2par(const QString &in, QString &label, IniParam &param, bool define = 1);

	bool		contains(const QString &label)		{return c_labels.contains(label);}
	int			count()								{return c_labels.count();}
	IniParam	&value(const QString &label)		{return *c_values[c_labels.indexOf(label)];}
	IniParam	&operator[](const QString &label)	{return value(label);}

	static QRegExp endWS()							{return QRegExp("^\\s|\\s$");}
};

#endif // INIITEM_H
