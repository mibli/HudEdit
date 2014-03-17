#include "hudscene.h"

HudScene::HudScene(QObject *parent) :
	BaseScene(parent)
{
}

HudItem *HudScene::addHudItem(IniItem* in)
{
	HudItem *item = new HudItem(in);
	addItem(item);
	return item;
}
