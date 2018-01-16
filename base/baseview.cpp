#include "baseview.h"

BaseView::BaseView(QWidget *parent) :
    QGraphicsView(parent)
{
    mouseGrabbed = 0;
}

void BaseView::wheelEvent(QWheelEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier)
    {
        if(event->delta() > 0)    zoomIn();
        else                    zoomOut();
        centerOn(mapToScene(event->pos()));
    }
    else    QGraphicsView::wheelEvent(event);
}

void BaseView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    if(selMode) loadSelection();
    mouseGrabbed = 1;
}

void BaseView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
    if(mouseGrabbed)
    {
        if(selMode == SubtractingSelection)        loadSubSelection();
        if(selMode == ExtendingSelection)        loadSelection();
    }
}

void BaseView::mouseReleaseEvent(QMouseEvent *event)
{
    if(dragMode() == RubberBandDrag && (event->modifiers() == Qt::ControlModifier || event->modifiers() == Qt::ShiftModifier))
    { saveSelection(); }
    QGraphicsView::mouseReleaseEvent(event);
    mouseGrabbed = 0;
}

void BaseView::keyPressEvent(QKeyEvent *event)
{
    if(dragMode() == RubberBandDrag && event->key() == Qt::Key_Control)
    { setSelectionMode(SubtractingSelection); }
    if(dragMode() == RubberBandDrag && event->key() == Qt::Key_Shift)
    { setSelectionMode(ExtendingSelection); }
    QGraphicsView::keyPressEvent(event);
}

void BaseView::keyReleaseEvent(QKeyEvent *event)
{
    if(dragMode() == RubberBandDrag && (event->key() == Qt::Key_Control || event->key() == Qt::Key_Shift))
    { setSelectionMode(DefaultSelection); }
    QGraphicsView::keyReleaseEvent(event);
}

void BaseView::setSelectionMode(SelectionMode mode)
{
    if(mode)    saveSelection();
    else        clearSavedSelection();
    selMode = mode;
}

void BaseView::saveSelection()
{
    selection = scene()->selectedItems();
}

void BaseView::loadSelection()
{
    for(int i=0; i<selection.count(); i++)
    { selection[i]->setSelected(true); }
}

void BaseView::loadSubSelection()
{
    QList<QGraphicsItem*> subselection = scene()->selectedItems();
    loadSelection();

    for(int i=0; i<subselection.count(); i++)
    { subselection[i]->setSelected(false); }
}
