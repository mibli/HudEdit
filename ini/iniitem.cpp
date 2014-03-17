#include "iniitem.h"

IniItem::IniItem()
{
}

bool IniItem::insert(const QString &line)
{
	QString label, value;
	if(lin2par(line,label,value))
	{
		c_labels << label;
		c_values.append(new IniParam(value));
		return true;
	}
	return false;
}

bool IniItem::load(const QStringList &lines)
{
	bool ok = 0; // if at least 1 line makes through it's ok;

	for(int i=0; i<lines.count(); i++)
	{
		ok = ok | insert(lines[i]);
	}

	if(!ok)
	{
		qDebug() << "IniItem::load failed (created item is empty)";
		return false;
	}
	return true;
}

QStringList IniItem::lines() const
{
	QStringList lns;

	for(int i=0; i<c_labels.count(); i++)
	{ lns << line(i); }

	return lns;
}

bool IniItem::lin2par(const QString &in, QString &label, QString &value)
{
	int i = in.indexOf(":");
	if( i != -1 )
	{
		label = in.left(i);
		value = in.right(in.length()-(i+1));
		if( !value.contains(":")  )
		{
			label.remove(endWS());
			value.remove(endWS());
			return true;
		}
		qDebug() << "IniItem::lin2par failed, multiple line split characters";
		return false;
	}
	qDebug() << "IniItem::lin2par failed, none line split characters";
	return false;
}

bool IniItem::lin2par(const QString &in, QString &label, IniParam &param, bool define)
{
	QString value;
	if( lin2par(in,label,value) )
	{
		if( define )
		{ param.load(value); }
		else
		{ param = value; }
		return true;
	}
	return false;
}
