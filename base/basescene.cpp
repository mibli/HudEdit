#include "basescene.h"

BaseScene::BaseScene(QObject *parent) :
	QGraphicsScene(parent)
{
	QBrush bgbrush(Qt::gray);
	setBackgroundBrush(bgbrush);
}

BaseItem *BaseScene::focusBaseItem() const
{
	return dynamic_cast<BaseItem*>(focusItem());
}

QList<BaseItem *> BaseScene::selectedBaseItems() const
{
	QList<QGraphicsItem*> origin = selectedItems();
	QList<BaseItem*> list;
	BaseItem* item;

	for(int i=0; i<origin.count(); i++)
	{
		item = dynamic_cast<BaseItem*>(origin[i]);
		if(item) list.append(item);
	}

	return list;
}

void BaseScene::emitItemSignals(const BaseItem *item, bool p, bool s)
{
	if(p)
	{
		emit itemMovedX(item->x());
		emit itemMovedY(item->y());
	}
	if(s)
	{
		emit itemChangedW(item->width());
		emit itemChangedH(item->height());
	}
}

void BaseScene::drawBackground(QPainter *painter, const QRectF &rect)
{
	QBrush fgbrush(Qt::white);
	QGraphicsScene::drawBackground(painter,rect);

	painter->fillRect(sceneRect(), fgbrush);
}

void BaseScene::alignTo(BaseScene::AlignTo f)
{
	QGraphicsItemGroup* group = dynamic_cast<QGraphicsItemGroup*>(focusItem());
	if(group)	alignSingle(focusItem(), f, 1);
	else
	{
		QList<QGraphicsItem*> list = selectedItems();
		if(list.count() == 1)		alignSingle(list[0], f);
		else if(list.count() > 0)	alignMultiple(list, f);
	}
}

void BaseScene::alignSingle(QGraphicsItem *item, BaseScene::AlignTo f, bool group)
{
	int xmod, ymod;
	xmod = ymod = 0;
	if(group)
	{
		xmod = item->boundingRect().x();
		ymod = item->boundingRect().y();
	}

	switch(f)
	{
	case Left:
		item->setX(0 - xmod);
		break;
	case Horizontal:
		item->setX(int((sceneRect().width() - item->boundingRect().width())/2) - xmod);
		break;
	case Right:
		item->setX(sceneRect().width() - item->boundingRect().width() - xmod);
		break;
	case Top:
		item->setY(0 - ymod);
		break;
	case Vertical:
		item->setY(int((sceneRect().height() - item->boundingRect().height())/2) - ymod);
		break;
	case Bottom:
		item->setY(sceneRect().height() - item->boundingRect().height() - ymod);
		break;
	}
	BaseItem* b_item = dynamic_cast<BaseItem*>(item);
	if(b_item)	emitItemSignals(b_item,1,0);
}

void BaseScene::alignMultiple(QList<QGraphicsItem *> list, BaseScene::AlignTo f)
{
	switch(f)
	{
	case Left:
		for(int i=0; i<list.count(); i++)
			list[i]->setX(list[0]->x());
		break;
	case Horizontal:
		for(int i=0; i<list.count(); i++)
			list[i]->setX(list[0]->x() + int((list[0]->boundingRect().width() - list[i]->boundingRect().width())/2));
		break;
	case Right:
		for(int i=0; i<list.count(); i++)
			list[i]->setX(list[0]->x() + list[0]->boundingRect().width() - list[i]->boundingRect().width());
		break;
	case Top:
		for(int i=0; i<list.count(); i++)
			list[i]->setY(list[0]->y());
		break;
	case Vertical:
		for(int i=0; i<list.count(); i++)
			list[i]->setY(list[0]->y() + int((list[0]->boundingRect().height() - list[i]->boundingRect().height())/2));
		break;
	case Bottom:
		for(int i=0; i<list.count(); i++)
			list[i]->setY(list[0]->y() + list[0]->boundingRect().height() - list[i]->boundingRect().height());
		break;
	}
}

void BaseScene::group()
{
	QList<QGraphicsItem*> items = selectedItems();
	if(items.count() > 1)
	{
		for(int i=0; i<items.count(); i++)
		{
			items[i]->setSelected(0);
			items[i]->setFlag(QGraphicsItem::ItemIsFocusable, 0);
			items[i]->setFlag(QGraphicsItem::ItemIsSelectable, 0);
			items[i]->setFlag(QGraphicsItem::ItemIsMovable, 0);
		}
		QGraphicsItemGroup* group = createItemGroup(items);
		group->setFlags(QGraphicsItemGroup::ItemIsSelectable | QGraphicsItemGroup::ItemIsFocusable | QGraphicsItemGroup::ItemIsMovable);
		group->setSelected(1);
		group->setFocus();
	}
}

void BaseScene::ungroup()
{
	QGraphicsItemGroup* group = dynamic_cast<QGraphicsItemGroup*>(focusItem());
	if(group)
	{
		QList<QGraphicsItem*> items = group->childItems();
		for(int i=0; i<items.count(); i++)
		{
			items[i]->setFlag(QGraphicsItem::ItemIsFocusable);
			items[i]->setFlag(QGraphicsItem::ItemIsSelectable);
			items[i]->setFlag(QGraphicsItem::ItemIsMovable);
			items[i]->setSelected(1);
		}
		destroyItemGroup(group);
	}
}

void BaseScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	BaseItem* item = dynamic_cast<BaseItem*>(itemAt(event->scenePos(), QTransform()));

	if(item && item->hasFocus() && editFlags & AllowItemResizing)
	{
		grabMouse = item->posAt(event->scenePos());
		if(grabMouse & ~(Hud::Inside))
		{
			return;
		}
		else	grabMouse = 0;
	}

	if(editFlags)
	{
		QGraphicsScene::mousePressEvent(event);
		if(item && item->hasFocus())
		{
			emitItemSignals(item);
			if(editFlags & AllowItemResizing)	item->setAcceptHoverEvents(1);
		}
	}
}

void BaseScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if(grabMouse)
	{
		BaseItem* item = static_cast<BaseItem*>(focusItem());
		item->adjust(event->screenPos()-event->lastScreenPos(), grabMouse);
		emitItemSignals(item);
		return;
	}

	if(editFlags)
	{
		QGraphicsScene::mouseMoveEvent(event);
		if(BaseItem* item = focusBaseItem()) emitItemSignals(item,1,0);
	}
}

void BaseScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if(grabMouse)
	{
		grabMouse = 0;
		return;
	}

	if(editFlags)
	{
		QGraphicsScene::mouseReleaseEvent(event);
	}
}
