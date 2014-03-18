#ifndef BASEVIEW_H
#define BASEVIEW_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>

class BaseView : public QGraphicsView
{
	Q_OBJECT
private:
	QList<QGraphicsItem*> selection;
	int selMode;

public:
	enum SelectionMode
	{
		DefaultSelection = 0,
		ExtendingSelection = 1,
		SubtractingSelection = 2
	};

	explicit BaseView(QWidget *parent = 0);

protected:
	void	wheelEvent(QWheelEvent *event);
	void	mousePressEvent(QMouseEvent *event);
	void	mouseMoveEvent(QMouseEvent *event);
	void	mouseReleaseEvent(QMouseEvent *event);
	void	keyPressEvent(QKeyEvent *event);
	void	keyReleaseEvent(QKeyEvent *event);

	void	setSelectionMode(SelectionMode mode);
	int		selectionMode()			{ return selMode; }
	void	saveSelection();
	void	loadSelection();
	void	loadSubSelection();
	void	clearSavedSelection()	{ selection.clear(); }

signals:

public slots:
	void	zoomIn()		{ scale(2,2); }
	void	zoomOut()		{ scale(0.5,0.5); }
	void	zoomReset()		{ matrix().reset(); }
};

#endif // BASEVIEW_H
