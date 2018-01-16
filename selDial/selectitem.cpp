#include "selectitem.h"

int SelectItem::checkRelativePosition(const QPoint &pos)
{
    int flags = Outside;
    if(bounds.contains(QRect(pos,QSize())))            flags += Inside;
    if( inItemRange(pos) )
    {
        if(abs(bounds.left()-pos.x()) <= tolerance)            flags += OnLeft;
        else if(abs(bounds.right()-pos.x()) <= tolerance)    flags += OnRight;
        if(abs(bounds.top()-pos.y()) <= tolerance)            flags += OnTop;
        else if(abs(bounds.bottom()-pos.y()) <= tolerance)    flags += OnBottom;
    }

    return flags;
}

void SelectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen bgPen( QColor(Qt::yellow) );
    QPen fgPen( QColor(Qt::black) );
    bgPen.setWidth(0);
    fgPen.setWidth(0);
    bgPen.setStyle(Qt::SolidLine);
    fgPen.setDashPattern( QVector<qreal>() << 3 << 3 );
    fgPen.setStyle(Qt::CustomDashLine);

    painter->setPen( bgPen );
    painter->drawRect( boundingRect() );
    painter->setPen( fgPen );
    painter->drawRect( boundingRect() );
}

void SelectItem::moveTop(int x)
{
    prepareGeometryChange();
    bounds.moveTop( x );
}

void SelectItem::moveLeft(int y)
{
    prepareGeometryChange();
    bounds.moveLeft( y );
}

void SelectItem::resizeBy(const QPoint &delta, int flags)
{
    int x1=0;
    int y1=0;
    int x2=0;
    int y2=0;

    if( flags & OnLeft )        { x1=delta.x(); }
    if( flags & OnRight )        { x2=delta.x(); }
    if( flags & OnTop )        { y1=delta.y(); }
    if( flags & OnBottom )        { y2=delta.y(); }

    prepareGeometryChange();
    bounds.adjust(x1,y1,x2,y2);
}
