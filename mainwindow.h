#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QList>
#include <QSharedPointer>
#include <QFileDialog>
#include "hud/hudscene.h"
#include "hud/huditem.h"
#include "ini/listfile.h"
#include "selDial/selectdialog.h"
#include "dialogs/about.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	enum FileMode { NoFile, ListOfFiles, SingleFile };

    explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

public slots:
	void load();
	void save();

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void keyPressEvent(QKeyEvent *e);

	void on_actionUV_Selector_triggered();
	void on_actionResize_triggered();
	void on_actionSelect_triggered();

	void on_actionItem_List_toggled(bool arg1);

	void on_actionZoom_In_triggered();
	void on_actionZoom_Out_triggered();

	void on_actionWiki_triggered();

private:
	Ui::MainWindow	*ui;
	FileMode		w_mode;
	ListFile*		w_list;
	HudScene*		w_scene;
	SelectDialog*	selectDialog;
	About*			about;
	int				editMode;
};

#endif // MAINWINDOW_H
