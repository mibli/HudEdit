#include "iniparam.h"

void IniParam::reset()
{
	if( c_number )
	{
		c_number = 0;
	}
	if( c_rect )
	{
		delete c_rect;
		delete c_res;
		c_rect = NULL;
		c_res = NULL;
	}
	if( c_point )
	{
		delete c_point;
		c_point = NULL;
	}
	if( c_string )
	{
		delete c_string;
		c_string = NULL;
	}
	c_type = NOTYPE;
}

void IniParam::zero()
{
	c_type		= NOTYPE;
	c_number	= 0;
	c_rect		= NULL;
	c_res		= NULL;
	c_point		= NULL;
	c_string	= NULL;
}

bool IniParam::load(const QString &data)
{
	reset();

	bool ok = 1;
	bool isInt;

	if( data.isEmpty() )
	{ c_type = NOTYPE; }
	if( data.contains("-") )
	{
		c_type = RECT;

		int i;
		QString rect_s, size_s;
		if( (i = data.indexOf("/")) != -1 )
		{
			rect_s = data.left(i);
			size_s = data.right(data.length()-(i+1));
		}
		else
		{
			rect_s = data;
		}

		QStringList vars;
		vars << rect_s.split("-");
		vars << vars[0].split(",");
		vars << vars[1].split(",");

		if(!(vars.count()<6))
		{
			c_rect = new QRectF;
			c_rect->setLeft		( vars[2].toDouble(&ok) );
			c_rect->setTop		( vars[3].toDouble(&ok) );
			c_rect->setRight	( vars[4].toDouble(&ok) );
			c_rect->setBottom	( vars[5].toDouble(&ok) );

			vars.clear();
			c_res = new QSize;
			if( !size_s.isEmpty() )
			{
				vars << size_s.split("x");
				if(!(vars.count()<2))
				{
					c_res->setWidth		( vars[0].toDouble(&ok) );
					c_res->setHeight	( vars[1].toDouble(&ok) );
				}
				else { qDebug() << "IniParam::load() warning, bad Resolution format"; }
			}
		}
		else { qDebug() << "IniParam::load() failure, bad Rect format"; }
	}
	else if( data.contains(",") && data.indexOf(",") == data.lastIndexOf(",") ) // if only 1 coma
	{
		c_type = POINT;

		QStringList vars;
		vars << data.split(",");

		c_point = new QPointF;
		c_point->setX( vars[0].toDouble(&ok) );
		c_point->setY( vars[1].toDouble(&ok) );
	}
    else if( (c_number = data.toInt(&isInt)) || isInt )
    { c_type = NUMBER; }
	else
	{
		c_type = STRING;
		c_string = new QString(data);
    }

	if(!ok){ qDebug() << "IniParam::load something went wrong"; }
}

QString IniParam::string() const
{
	if( c_type == STRING )
	{ return *c_string; }
	else if( c_type == NUMBER )
	{ return QString::number(c_number); }
	else if( c_type == POINT )
	{
		QString text = QString("%1,%2").arg(
					QString::number(c_point->x()),
					QString::number(c_point->y()));
		return text;
	}
	else if( c_type == RECT )
	{
		QString text = QString("%1,%2 - %3,%4").arg(
					QString::number(c_rect->left()),
					QString::number(c_rect->top()),
					QString::number(c_rect->right()),
					QString::number(c_rect->bottom()));
		if( !c_res->isEmpty() )
		{
			text += QString(" /%1x%2").arg(
						QString::number(c_res->width()),
						QString::number(c_res->height()));
		}
		return text;
	}
	else
	{ return ""; }
}

bool IniParam::isEmpty() const
{
	if( isNull() )
	{ return true; }
	else if( c_type == NUMBER )
	{ return !bool(abs(c_number)); }
	else if( c_type == RECT )
	{ return c_rect->isEmpty(); }
	else if( c_type == POINT )
	{ return c_point->isNull(); }
	else if( c_type == STRING )
	{ return c_string->isEmpty(); }
	else
	{ return true; }
}

QRect IniParam::rect(bool translated, const QPointF &anchor) const
{
	if( c_type == RECT )
	{
		if( translated )
		{
			QRectF rect_t = *c_rect;
			rect_t.setLeft		(qRound( c_rect->left() / Hud::xVar ));
			rect_t.setTop		(qRound( c_rect->top() / Hud::yVar ));
			rect_t.setRight		(qRound( c_rect->right() / Hud::xVar ));
			rect_t.setBottom	(qRound( c_rect->bottom() / Hud::yVar ));

			if( !anchor.isNull() )
			{ rect_t.translate(offset(anchor)); }

			return rect_t.toRect();
		}
		return c_rect->toRect();
	}
	return QRect();
}

void IniParam::setRect(const QRect &r, bool translate, const QPointF &anchor)
{
	if( c_type == RECT )
	{
		*c_rect = r;

		if( translate )
		{
			if( !anchor.isNull() )
			{ c_rect->translate(-offset(anchor)); }

			c_rect->setLeft		( c_rect->left() * Hud::xVar );
			c_rect->setTop		( c_rect->top() * Hud::yVar );
			c_rect->setRight	( c_rect->right() * Hud::xVar );
			c_rect->setBottom	( c_rect->bottom() * Hud::yVar );
		}
	}
}

QPoint IniParam::offset(const QPointF &anchor) const
{
	return QPoint(
				(Hud::xRes-res(1).width())*anchor.x(),
				(Hud::yRes-res(1).height())*anchor.y() );
}

QSize IniParam::res(bool translated) const
{
	if( c_type == RECT )
	{
		if( translated )
		{
			return QSize(c_res->width() / Hud::xVar, c_res->height() / Hud::yVar);
		}
		return *c_res;
	}
	return QSize();
}

