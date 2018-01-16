#include "baseitem.h"

BaseItem::BaseItem(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    setFlag(ItemSendsGeometryChanges);
}

void BaseItem::setWidth(int w)
{
    prepareGeometryChange();

    if(abs(w) < Hud::MinSize)
    {
        w = (w<0)? -1 : 1;
        bSize.setWidth(Hud::MinSize * w);
    }
    else
    {
        bSize.setWidth(w);
    }
}

void BaseItem::setHeight(int h)
{
    prepareGeometryChange();

    if(abs(h) < Hud::MinSize)
    {
        h = (h<0)? h=-1 : h=1;
        bSize.setWidth(Hud::MinSize * h);
    }
    else
    {
        bSize.setHeight(h);
    }
}

int BaseItem::posAt(const QPointF &p, const QRectF &r)
{
    int f = 0;
    QRectF re = r.isEmpty() ? realRect() : r;

         if( re.contains(p) )                                    f += Hud::Inside;
         if( abs(re.x() - p.x()) <= tolerance() )                f += Hud::OverLeft;
    else if( abs(re.x() + re.width() - p.x()) <= tolerance() )    f += Hud::OverRight;
         if( abs(re.y() - p.y()) <= tolerance() )                f += Hud::OverTop;
    else if( abs(re.y() + re.height() - p.y()) <= tolerance() )    f += Hud::OverBottom;

    return f;
}

void BaseItem::adjust(const QPointF &p, int f)
{
    int x1,x2,y1,y2;
    x1=x2=y1=y2=0;

         if(f & Hud::OverLeft)        x1 = p.x();
    else if(f & Hud::OverRight)        x2 = p.x();
         if(f & Hud::OverTop)        y1 = p.y();
    else if(f & Hud::OverBottom)    y2 = p.y();

    adjust(x1,y1,x2,y2);
}

void BaseItem::adjust(int x1, int y1, int x2, int y2)
{
    moveBy(x1,y1);
    setWidth(width()-x1+x2);
    setHeight(height()-y1+y2);
}

QVariant BaseItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemPositionHasChanged)
    {
        moved = 1;
        if(pos() != pos().toPoint())
        {
            setPos( pos().toPoint() );
        }
    }
    if(change == ItemSelectedHasChanged)
    {
        if(isSelected())    setZValue(zValue()+10);
        else                setZValue(zValue()-10);
    }
    return QGraphicsItem::itemChange(change, value);
}

void BaseItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if(hasFocus())
    {
        int f = posAt(event->scenePos(), rect().translated(pos()));

             if(f & Hud::OverTop && f & Hud::OverLeft)        setCursor(QCursor(Qt::SizeFDiagCursor));
        else if(f & Hud::OverTop && f & Hud::OverRight)        setCursor(QCursor(Qt::SizeBDiagCursor));
        else if(f & Hud::OverBottom && f & Hud::OverLeft)    setCursor(QCursor(Qt::SizeBDiagCursor));
        else if(f & Hud::OverBottom && f & Hud::OverRight)    setCursor(QCursor(Qt::SizeFDiagCursor));
        else if(f & Hud::OverLeft)                            setCursor(QCursor(Qt::SizeHorCursor));
        else if(f & Hud::OverTop)                            setCursor(QCursor(Qt::SizeVerCursor));
        else if(f & Hud::OverRight)                            setCursor(QCursor(Qt::SizeHorCursor));
        else if(f & Hud::OverBottom)                        setCursor(QCursor(Qt::SizeVerCursor));
        else                                                setCursor(QCursor(Qt::ArrowCursor));
    }
}
