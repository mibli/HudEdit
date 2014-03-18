#ifndef BASESCENE_H
#define BASESCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QDebug>
#include "baseitem.h"

class BaseScene : public QGraphicsScene
{
	Q_OBJECT
private:
	QImage	texture;
	int		grabMouse = 0;
	int		editFlags;
	int		selectMode = 0;
public:
	explicit BaseScene(QObject *parent = 0);

	enum	EditFlags
	{
		DisallowAll			= 0,
		AllowItemMovement	= 1ul << 0,
		AllowItemResizing	= 1ul << 1,
		AllowItemSelection	= 1ul << 2
	};
	enum	SelectMode
	{
		Default				= 0,
		Subtract			= 1,
		Expand				= 2
	};

	BaseItem*			focusBaseItem() const;
	QList<BaseItem*>	selectedBaseItems() const;
	void				emitItemSignals(const BaseItem* item, bool p=1, bool s=1);
	void				drawBackground(QPainter *painter, const QRectF &rect);

	void	setEditFlag(EditFlags f)		{ editFlags |= f; }
	void	setEditFlags(EditFlags f)		{ editFlags = f; }

signals:
	void	itemMovedX(int);
	void	itemMovedY(int);
	void	itemChangedW(int);
	void	itemChangedH(int);
public slots:
	/* for Align */
	void	alignLeft();
	void	alignRight();
	void	centerHorizontal();
	void	alignTop();
	void	alignBottom();
	void	centerVertical();
	/* for Spinboxes */
	void	itemSetX(int x)				{ if(BaseItem* item = dynamic_cast<BaseItem*>(focusItem())) item->setX(x); }
	void	itemSetY(int y)				{ if(BaseItem* item = dynamic_cast<BaseItem*>(focusItem())) item->setY(y); }
	void	itemSetW(int w)				{ if(BaseItem* item = dynamic_cast<BaseItem*>(focusItem())) item->setWidth(w); }
	void	itemSetH(int h)				{ if(BaseItem* item = dynamic_cast<BaseItem*>(focusItem())) item->setHeight(h); }
protected:
	void	mousePressEvent(QGraphicsSceneMouseEvent *event);
	void	mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void	mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void	keyPressEvent(QKeyEvent *event);
};

#endif // BASESCENE_H
