#include "selectscene.h"

SelectScene::SelectScene(QObject *parent) :
    QGraphicsScene(parent)
{
    mouseFlags = 0;
    selectItem = addSelect(0,0,0,0);
}

SelectItem* SelectScene::addSelect(int x, int y, int w, int h)
{
    SelectItem* item = new SelectItem(x,y,w,h);
    addItem(item);
    return item;
}

bool SelectScene::setImage(const QImage &image)
{
    bgImage = image;
    setSceneRect( QRect(QPoint(),image.size()) );
}

void SelectScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QBrush brush;
    QGraphicsScene::drawBackground(painter, rect);

    brush.setColor(Qt::lightGray);
    painter->fillRect( sceneRect(), brush );

    brush.setTextureImage(bgImage);
    painter->fillRect( sceneRect(), brush );
}

void SelectScene::keyPressEvent(QKeyEvent *event)
{
    int inc = 1;
    if( event->modifiers() & Qt::ShiftModifier )        inc = 5;
    if( event->modifiers() & Qt::ControlModifier )    inc *= 10;

    QPoint delta;
    if( event->key() == Qt::Key_Up )        delta.setY(-inc);
    else if( event->key() == Qt::Key_Down )    delta.setY(inc);
    if( event->key() == Qt::Key_Left )        delta.setX(-inc);
    else if( event->key() == Qt::Key_Right )    delta.setX(inc);

    selectItem->moveBy(delta);
}

void SelectScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    mouseFlags = selectItem->checkRelativePosition( event->scenePos().toPoint() );

    if( mouseFlags & (~SelectItem::Inside) )    { mode = Resizing; }
    else if( mouseFlags & SelectItem::Inside )    { mode = Moving; }
    else
    {
        mode = Selecting;
        selectItem->setFirst( event->scenePos().toPoint() );
    }
}

void SelectScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if( mode == Resizing )
    {
        QPoint delta = ( event->scenePos() - event->lastScenePos() ).toPoint();
        selectItem->resizeBy(delta, mouseFlags);
    }
    else if( mode == Moving )
    {
        QPoint delta = ( event->scenePos() - event->lastScenePos() ).toPoint();
        selectItem->moveBy(delta);
    }
    else if( mode == Selecting )
    {
        selectItem->setSecond( event->scenePos().toPoint() );
    }
}

void SelectScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    mode = Idle;

    emit updated();
    emit xChanged( selectItem->rect().x() );
    emit yChanged( selectItem->rect().y() );
    emit widthChanged( selectItem->rect().width() );
    emit heightChanged( selectItem->rect().height() );
}

void SelectScene::select(int x, int y, int w, int h)
{
    if(QRect(x,y,w,h) != selectItem->rect())
    {
        setX(x);
        setY(y);
        setWidth(w);
        setHeight(h);
        emit updated();
        emit xChanged( selectItem->rect().x() );
        emit yChanged( selectItem->rect().y() );
        emit widthChanged( selectItem->rect().width() );
        emit heightChanged( selectItem->rect().height() );
    }
}

void SelectScene::setX(int x)        { if( x != selectItem->x() ) selectItem->moveLeft(x); }

void SelectScene::setY(int y)        { if( y != selectItem->y() ) selectItem->moveTop(y); }

void SelectScene::setWidth(int w)    { if( w != selectItem->width() ) selectItem->setWidth(w); }

void SelectScene::setHeight(int h)    { if( h != selectItem->height() ) selectItem->setHeight(h); }
