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

	for(int i; i<origin.count(); i++)
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

void BaseScene::alignLeft()
{
	QList<BaseItem*> list = selectedBaseItems();

	if(list.count() == 1)
	{
		list[0]->setX(0);
		emitItemSignals(list[0],1,0);
	}
	else if(list.count() > 0)
	{
		int ext = list[0]->x();
		for(int i=0; i<list.count(); i++)		list[i]->setX(ext);
	}
}

void BaseScene::alignRight()
{
	QList<BaseItem*> list = selectedBaseItems();

	if(list.count() == 1)
	{
		list[0]->setX(sceneRect().right() - abs(list[0]->width()));
		emitItemSignals(list[0],1,0);
	}
	else if(list.count() > 0)
	{
		int ext = list[0]->x() + abs(list[0]->width());
		for(int i=0; i<list.count(); i++)		list[i]->setX(ext - abs(list[i]->width()));
	}
}

void BaseScene::centerHorizontal()
{
	QList<BaseItem*> list = selectedBaseItems();

	if(list.count() == 1)
	{
		list[0]->setX(sceneRect().right() - qRound(qreal(abs(list[0]->width()) / 2)));
		emitItemSignals(list[0],1,0);
	}
	else if(list.count() > 0)
	{
		int ext = list[0]->x() + qRound(qreal(abs(list[0]->width())) / 2);
		for(int i=0; i<list.count(); i++)		list[i]->setX(ext - qRound(qreal(abs(list[i]->width()) / 2)));
	}
}

void BaseScene::alignTop()
{
	QList<BaseItem*> list = selectedBaseItems();

	if(list.count() == 1)
	{
		list[0]->setY(0);
		emitItemSignals(list[0],1,0);
	}
	else if(list.count() > 0)
	{
		int ext = list[0]->y();
		for(int i=0; i<list.count(); i++)		list[i]->setY(ext);
	}
}

void BaseScene::alignBottom()
{
	QList<BaseItem*> list = selectedBaseItems();

	if(list.count() == 1)
	{
		list[0]->setY(sceneRect().bottom() - abs(list[0]->height()));
		emitItemSignals(list[0],1,0);
	}
	else if(list.count() > 0)
	{
		int ext = list[0]->y() + abs(list[0]->height());
		for(int i=0; i<list.count(); i++)		list[i]->setY(ext - abs(list[i]->height()));
	}
}

void BaseScene::centerVertical()
{
	QList<BaseItem*> list = selectedBaseItems();

	if(list.count() == 1)
	{
		list[0]->setY(sceneRect().bottom() - qRound(qreal(abs(list[0]->height()) / 2)));
		emitItemSignals(list[0],1,0);
	}
	else if(list.count() > 0)
	{
		int ext = list[0]->y() + qRound(qreal(abs(list[0]->height()) / 2));
		for(int i=0; i<list.count(); i++)		list[i]->setY(ext - qRound(qreal(abs(list[i]->height()) / 2)));
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

void BaseScene::keyPressEvent(QKeyEvent *event)
{
}
