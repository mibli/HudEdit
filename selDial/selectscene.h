#ifndef UVSCENE_H
#define UVSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>
#include "selDial\selectitem.h"

class SelectScene : public QGraphicsScene
{
	Q_OBJECT
public:
	explicit SelectScene(QObject *parent = 0);
private:
	enum EditMode { Idle, Selecting, Moving, Resizing  };
	EditMode mode;
	int mouseFlags;
	QImage bgImage;
	SelectItem* selectItem = 0;
protected:
	void keyPressEvent(QKeyEvent* event);
	void mousePressEvent( QGraphicsSceneMouseEvent* event );
	void mouseMoveEvent( QGraphicsSceneMouseEvent* event );
	void mouseReleaseEvent( QGraphicsSceneMouseEvent* event );
public:
	SelectItem* addSelect(int x, int y, int w, int h);
	bool setImage(const QImage &image);
	bool grabHandlesAt(const QPoint &point);
	bool resizeBy(const QPoint &delta);
	void drawBackground(QPainter * painter, const QRectF & rect);
signals:
	void updated();
	void xChanged(int);
	void yChanged(int);
	void widthChanged(int);
	void heightChanged(int);
	void mouseOver(int);
public slots:
	void select(int x, int y, int w, int h);
	void setX(int x);
	void setY(int y);
	void setWidth(int w);
	void setHeight(int h);
};

#endif // UVSCENE_H
