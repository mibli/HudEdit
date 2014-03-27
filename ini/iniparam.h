#ifndef INIPARAMS_H
#define INIPARAMS_H

#include "Hud.h"
#include <QRectF>
#include <QPointF>
#include <QSize>
#include <QStringList>
#include <QDebug>

class IniParam
{
public:
	enum _type { NOTYPE, NUMBER, RECT, POINT, STRING };
private:
	enum _type	c_type;
	int			c_number;
	QPointF*	c_point;
	QRectF*		c_rect;
	QSize*		c_res;
	QString*	c_string;
public:
	IniParam()						{ zero(); }
	IniParam(const IniParam &in)	{ zero(); load(in.string()); }
	IniParam(const QString &data)	{ zero(); load(data); }
	~IniParam()						{ zero(); reset(); }


private:
	void reset();
	void zero();

public:
	bool load(const QString &data);

	bool	isNull()	const { return c_type == NOTYPE; }
	bool	isEmpty()	const;
	bool	isNumber()	const { return c_type == NUMBER; }
	bool	isRect()	const { return c_type == RECT; }
	bool	isPoint()	const { return c_type == POINT; }
	bool	isString()	const { return c_type == STRING; }

	void operator<<(const QString &in)		{ load(in); }

	//converions
	QRect	rect(bool translated = 0, const QPointF &anchor = QPoint()) const;
	void	setRect(const QRect &r, bool translate = 0, const QPointF &anchor = QPoint());
	QPoint	offset(const QPointF &anchor) const;
	QSize	res(bool translated = 0) const;

	int		integer()	const				{ if( c_type == NUMBER )	return c_number;	else return 0; }
	QRectF	rectf()		const				{ if( c_type == RECT )		return *c_rect;		else return QRectF(); }
	QPointF	point()		const				{ if( c_type == POINT )		return *c_point;	else return QPointF(); }
	QString string()	const;
	operator QString()	const				{ if( c_type == STRING )	return *c_string;	else return string(); }
	void operator=(const int &in)			{ if( c_type == NUMBER )		c_number	= in; }
	void operator=(const QPointF &in)		{ if( c_type == POINT )			*c_point	= in; }
	void operator=(const QRectF &in)		{ if( c_type == RECT )			*c_rect	= in; }
	void operator=(const QSize &in)			{ if( c_type == RECT )			*c_res	= in; }
	void operator=(const QString &in)		{ if( c_type == STRING )		*c_string	= in;
											  else if( c_type == NOTYPE )	load(in); }
};

#endif // INIPARAMS_H
