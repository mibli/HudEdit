#include "hudscene.h"

HudScene::HudScene(QObject *parent) :
    BaseScene(parent)
{}

HudItem* HudScene::addHudItem(IniItem* in)
{
    HudItem* item = new HudItem(in);
    addItem(item);
    hudItemList.append(item);
    return item;
}

QList<HudItem *> HudScene::hudItems()
{
    return hudItemList;
}


