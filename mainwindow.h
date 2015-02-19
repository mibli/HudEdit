#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QList>
#include <QFileDialog>
#include <QMessageBox>
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
    void load_image();
	void save();

private slots:
	void on_actionUV_Selector_triggered();
	void on_actionResize_triggered();
	void on_actionSelect_triggered();

	void on_actionZoom_In_triggered();
	void on_actionZoom_Out_triggered();

	void on_actionWiki_triggered();
	void onUVin(int x1, int y1, int x2, int y2);

private:
	Ui::MainWindow	*ui;
	FileMode		w_mode;
	ListFile*		w_list;
	HudScene*		w_scene;
	SelectDialog*	selectDialog;
	About*			about;
	int				editMode;
	QImage			HUDAtlas;
	QImage			bgImage;
	QSize			resolution;
};

#endif // MAINWINDOW_H
