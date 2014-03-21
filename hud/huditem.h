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
	QString		getName()				{ return (*iniItem)["Name"]; }
	bool		hasAtlas()				{ return (*iniItem)["Texture"].toString().contains("HUDAtlas", Qt::CaseInsensitive); }
	bool		hasUV()					{ return iniItem->contains("UV"); }
	QRectF		getUV()					{ if(hasUV()) return (*iniItem)["UV"].toQRectF(); else return QRectF(); }
	void		setUV(const QRectF &r)	{ if(hasUV()) (*iniItem)["UV"] = r; }
	void		save()					{ (*iniItem)["Rect"] = BaseItem::realRect(); }

private:
	QImage		texture;
	IniItem*	iniItem;
};

#endif // HUDELEMENT_H
