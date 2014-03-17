#ifndef HUDSCENE_H
#define HUDSCENE_H

#include <QGraphicsScene>
#include <QList>
#include <QRubberBand>
#include "huditem.h"
#include "base/basescene.h"
#include "Hud.h"

class HudScene : public BaseScene
{
	Q_OBJECT
public:
	explicit HudScene(QObject *parent = 0);

	HudItem*	addHudItem(IniItem* in);

public slots:
	void	select(QGraphicsItem* item)		{ deselectAll(); item->setSelected(1); }
	void	selectAdd(QGraphicsItem* item)	{ item->setSelected(1); }
	void	deselect(QGraphicsItem* item)	{ item->setSelected(0); }
	void	deselectAll()					{ this->setSelectionArea(QPainterPath()); }
};

#endif // HUDSCENE_H
