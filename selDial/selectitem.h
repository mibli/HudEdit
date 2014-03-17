#ifndef SELECTITEM_H
#define SELECTITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

class SelectItem : public QGraphicsItem
{
private:
	QRect bounds;
public:
	explicit SelectItem() : QGraphicsItem() {}
	SelectItem(int x, int y, int w, int h) : bounds(x,y,w,h), QGraphicsItem() {}
	SelectItem(const QRect &rect) : bounds(rect), QGraphicsItem() {}

	// flags for resizing mainly
	const int tolerance = 4;
	enum RelPosition
	{
		Outside = 0,
		Inside = 1,
		OnLeft = 2,
		OnTop = 4,
		OnRight = 8,
		OnBottom = 16
	};
	RelPosition relative;
	int checkRelativePosition(const QPoint &point);
	int inItemRange(const QPoint &point)	{ return bounds.adjusted(-tolerance,-tolerance,tolerance,tolerance).intersects(QRect(point, QSize(1,1))); }

	// essentials
	QRectF boundingRect() const		{ return bounds.normalized(); }
	QRect rect() const				{ return bounds; }
	void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );

	// selecting
	void setRect( const QRect &rect )		{ prepareGeometryChange(); bounds = rect; }
	void setFirst( const QPoint &point )	{ prepareGeometryChange(); bounds.setSize(QSize(0,0)); bounds.moveTopLeft( point ); }
	void setSecond( const QPoint &point )	{ prepareGeometryChange(); bounds.setBottomRight( point ); }

	// movement
	int x() const		{ return bounds.x(); }
	int y() const		{ return bounds.y(); }
	int width() const		{ return bounds.width(); }
	int height() const	{ return bounds.height(); }
	void moveBy(const QPoint &delta) { prepareGeometryChange(); bounds.moveTopLeft(bounds.topLeft() + delta); }
	void moveTop(int x);
	void moveLeft(int y);
	void setWidth(int w)		{ prepareGeometryChange(); bounds.setWidth( w ); }
	void setHeight(int h)		{ prepareGeometryChange(); bounds.setHeight( h ); }
	void resizeBy(const QPoint &delta, int flags);
	void adjust(int x1, int y1, int x2, int y2)	{ prepareGeometryChange(); bounds.adjust(x1,y1,x2,y2); }
};

#endif // SELECTITEM_H
