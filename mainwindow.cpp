#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	w_scene = new HudScene(this);
	ui->screen->setScene(w_scene);
	w_scene->setSceneRect(0,0,1024,768);

	ui->screen->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);

	w_mode = NoFile;

	connect(w_scene,SIGNAL(itemMovedX(int)),ui->xBox,SLOT(setValue(int)));
	connect(w_scene,SIGNAL(itemMovedY(int)),ui->yBox,SLOT(setValue(int)));
	connect(w_scene,SIGNAL(itemChangedW(int)),ui->widthBox,SLOT(setValue(int)));
	connect(w_scene,SIGNAL(itemChangedH(int)),ui->heightBox,SLOT(setValue(int)));
	connect(ui->actionAlign_Left,SIGNAL(triggered()),w_scene,SLOT(alignLeft()));
	connect(ui->actionCenter_Horizontally,SIGNAL(triggered()),w_scene,SLOT(centerHorizontal()));
	connect(ui->actionAlign_Right,SIGNAL(triggered()),w_scene,SLOT(alignRight()));
	connect(ui->actionAlign_Top,SIGNAL(triggered()),w_scene,SLOT(alignTop()));
	connect(ui->actionCenter_Vertically,SIGNAL(triggered()),w_scene,SLOT(centerVertical()));
	connect(ui->actionAlign_Bottom,SIGNAL(triggered()),w_scene,SLOT(alignBottom()));
	connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(load()));
	connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(save()));
	connect(ui->actionGroup,SIGNAL(triggered()),w_scene,SLOT(group()));
	connect(ui->actionUngroup,SIGNAL(triggered()),w_scene,SLOT(ungroup()));

	selectDialog = new SelectDialog(this);
	connect(selectDialog,SIGNAL(rectSelected(int,int,int,int)),this,SLOT(onUVin(int,int,int,int)));

	about = new About(this);
	connect(ui->actionAbout,SIGNAL(triggered()),about,SLOT(show()));

	editMode = 0;
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::load()
{
	QString path = QFileDialog::getOpenFileName(this,"Open Ini","","ElementList Ini (*.ini)");

	if(!path.isEmpty())
	{
		w_list = new ListFile(path);

		QList<IniItem*> itemlist;
		itemlist << w_list->getAll();

		for(int i=0;i<itemlist.count();i++)
		{
			w_scene->addHudItem(itemlist[i]);
		}
		qDebug() << itemlist.count();
	}
	else
	{
		qDebug() << "MainWindow::load - user canceled";
	}
}

void MainWindow::loadImage()
{
	QString path = QFileDialog::getOpenFileName(0,"Open Texture File","","(hudatlas.png)");
	if(!path.isEmpty())
	{
		if(!HUDAtlas.load(path))
			qDebug() << "MainWindow::loadImg failure - couldn't load the img";
	}
	else
		qDebug() << "MainWindow::loadImg - user canceled";
}

void MainWindow::save()
{
	w_list->save();
}

void MainWindow::on_actionUV_Selector_triggered()
{
	HudItem* item = dynamic_cast<HudItem*>(w_scene->focusItem());
	if(item)
	{
		if(item->hasUV())
		{
			if(item->hasAtlas())
			{
				if(HUDAtlas.isNull())	loadImage();
				if(!HUDAtlas.isNull())	selectDialog->loadImage(HUDAtlas);
				selectDialog->selectRect(item->getUV().toRect());
				//ui->setEnabled(false);
			}
		}
		else	QMessageBox::information(this,"No UV","This item doesn't have texture property",QMessageBox::Ok);
	}
	else	QMessageBox::information(this,"No focused item","Please focus an item first",QMessageBox::Ok);
}

void MainWindow::on_actionResize_triggered()
{
	ui->actionResize->setChecked(1);
	ui->actionSelect->setChecked(0);

	editMode = 0;
	ui->screen->setDragMode(QGraphicsView::NoDrag);
	w_scene->setEditFlag(BaseScene::AllowItemResizing);
	w_scene->setEditFlag(BaseScene::AllowItemSelection);
}

void MainWindow::on_actionSelect_triggered()
{
	ui->actionResize->setChecked(0);
	ui->actionSelect->setChecked(1);

	editMode = 1;
	ui->screen->setDragMode(QGraphicsView::RubberBandDrag);
	ui->screen->setRubberBandSelectionMode(Qt::ContainsItemShape);
	w_scene->setEditFlags(BaseScene::DisallowAll);
}

void MainWindow::on_actionItem_List_toggled(bool arg1)
{
/*	if(ui->actionItem_List->isChecked())
		ui->itemList->setVisible(1);
	else
		ui->itemList->setVisible(0);
		*/
}

void MainWindow::on_actionZoom_In_triggered()			{ ui->screen->scale(2,2); }

void MainWindow::on_actionZoom_Out_triggered()			{ ui->screen->scale(0.5,0.5); }

void MainWindow::on_actionWiki_triggered()				{ QDesktopServices::openUrl(QUrl("https://sourceforge.net/p/hudedit/wiki/Home/")); }

void MainWindow::onUVin(int x1, int y1, int x2, int y2)
{
	QRect r(x1,y1,x2-x1,y2-y1);
	HudItem* item = static_cast<HudItem*>(w_scene->focusItem());
	item->setUV(r);
	this->setEnabled(true);
}
