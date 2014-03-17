#ifndef HUDELEMENT_H
#define HUDELEMENT_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QKeyEvent>
#include <QKeySequence>
#include <QLineEdit>
#include "Hud.h"
#include "../ini/iniitem.h"
#include "../base/baseitem.h"

class HudItem : public BaseItem
{
public:
	HudItem(IniItem* item, QGraphicsItem *parent=0);
	~HudItem();

	QRectF boundingRect() const	{ return BaseItem::boundingRect(); }
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	bool resize(int deltaWidth, int deltaHeight);

private:
	QImage		texture;
	IniItem*	iniItem;
};

#endif // HUDELEMENT_H
