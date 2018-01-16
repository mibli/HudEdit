#include "selectdialog.h"
#include "ui_selectdialog.h"

SelectDialog::SelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectDialog)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window);

    selectScene = new SelectScene;
    ui->graphicsView->setScene(selectScene);

    connect(ui->xBox,SIGNAL(valueChanged(int)),selectScene,SLOT(setX(int)));
    connect(ui->yBox,SIGNAL(valueChanged(int)),selectScene,SLOT(setY(int)));
    connect(ui->widthBox,SIGNAL(valueChanged(int)),selectScene,SLOT(setWidth(int)));
    connect(ui->heightBox,SIGNAL(valueChanged(int)),selectScene,SLOT(setHeight(int)));

    connect(selectScene,SIGNAL(xChanged(int)),ui->xBox,SLOT(setValue(int)));
    connect(selectScene,SIGNAL(yChanged(int)),ui->yBox,SLOT(setValue(int)));
    connect(selectScene,SIGNAL(widthChanged(int)),ui->widthBox,SLOT(setValue(int)));
    connect(selectScene,SIGNAL(heightChanged(int)),ui->heightBox,SLOT(setValue(int)));

    connect(ui->doneButton,SIGNAL(clicked()),this,SLOT(doneSelecting()));
}

SelectDialog::~SelectDialog()
{
    delete ui;
}

bool SelectDialog::loadImage(const QString &path)
{
    texture.load(path);
    selectScene->setImage(texture);
}

bool SelectDialog::loadImage(const QImage &image)
{
    texture = image;
    selectScene->setImage(texture);
}

void SelectDialog::selectRect(const QRect &r)
{
    selectScene->select(r.x(),r.y(),r.width(),r.height());
    show();
}

void SelectDialog::doneSelecting()
{
    emit rectSelected(
                ui->xBox->value(),
                ui->yBox->value(),
                ui->xBox->value() + ui->widthBox->value(),
                ui->yBox->value() + ui->heightBox->value()
                );
    hide();
}

void SelectDialog::selectRect(int x1, int y1, int x2, int y2)
{
    selectScene->select( x1, y1, x1-x2, y1-y2 );
    show();
}
