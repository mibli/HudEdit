#include "huditem.h"


HudItem::HudItem(IniItem *item, QGraphicsItem *parent) : BaseItem(parent)
{
	setFlag(QGraphicsItem::ItemSendsGeometryChanges);
	setFlag(QGraphicsItem::ItemIsFocusable);
	setFlag(QGraphicsItem::ItemIsSelectable);
	setFlag(QGraphicsItem::ItemIsMovable);
	iniItem = item;

	BaseItem::setRect((*iniItem)["Rect"].toQRectF());
	setZValue( (*iniItem)["Layer"].toInt() ); // setting layer;
}

HudItem::~HudItem()
{
	(*iniItem)["Rect"] = rect();
}

void HudItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen bgpen(Qt::black), fgpen(Qt::transparent);
	QBrush brush(QColor(127,127,127,40));
	QVector<qreal> pattern;
	pattern << 3 << 3;

	qreal inc = 1/scale();

	bgpen.setWidth(inc);
	fgpen.setWidth(inc);
	bgpen.setStyle(Qt::SolidLine);
	fgpen.setDashPattern(pattern);
	fgpen.setStyle(Qt::CustomDashLine);

	if(hasFocus() && isSelected())
	{ fgpen.setColor(Qt::white); }
	else if(isSelected())
	{ fgpen.setColor(QColor(255,255,126)); }

	if(!texture.isNull())	painter->drawImage(0, 0, texture);
	else			painter->fillRect(rect().normalized(),brush);
	painter->setPen(bgpen);
	painter->drawRect(rect().normalized().adjusted(inc/2,inc/2,-inc/2,-inc/2));
	painter->setPen(fgpen);
	painter->drawRect(rect().normalized().adjusted(inc/2,inc/2,-inc/2,-inc/2));
}
