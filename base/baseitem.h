#ifndef BASEITEM_H
#define BASEITEM_H

#include <QGraphicsItem>
#include <QGraphicsSceneHoverEvent>
#include <QCursor>
#include <QSize>
#include <QDebug>
#include "Hud.h"

class BaseItem : public QGraphicsItem
{
private:
	int		Tolerance = 3;
	QSize	bSize;
	bool	moved;
public:
	BaseItem(QGraphicsItem* parent);

	/* basic geometry */
	QRectF	rect() const				{ return QRectF(QPoint(), bSize).normalized(); }
	QRectF	realRect() const			{ return QRectF(pos(), bSize); }
	QRectF	boundingRect() const		{ return rect(); }
	QSize	size() const				{ return QSize(width(),height()); }
	qreal	width() const				{ return bSize.width(); }
	qreal	height() const				{ return bSize.height(); }
	void	setRect(const QRectF &r)	{ setPos(r.topLeft().toPoint()); setSize(r.size().toSize()); }
	void	setSize(const QSize &s)		{ setSize(s.width(), s.height()); }
	void	setSize(int w, int h)		{ setWidth(w); setHeight(h); }
	void	setWidth(int w);
	void	setHeight(int h);
	bool	hasMoved()					{ if(moved){moved = 0; return 1;}else{return 0;} }

	/* adjusting geometry */
	int		posAt(const QPointF &p, const QRectF &r = QRectF());
	void	adjust(const QPointF &p, int f);
	void	adjust(int x1, int y1, int x2, int y2);
	qreal	tolerance() const			{ return Tolerance*(1/scale()); }

protected:
	QVariant	itemChange(GraphicsItemChange change, const QVariant &value);
	void	hoverMoveEvent(QGraphicsSceneHoverEvent *event);
	void	focusOutEvent(QFocusEvent *event)	{setCursor(QCursor(Qt::ArrowCursor)); setAcceptHoverEvents(0);}
};

#endif // BASEITEM_H
