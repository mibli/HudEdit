#ifndef SELECTDIALOG_H
#define SELECTDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <selDial\selectscene.h>

namespace Ui {
class SelectDialog;
}

class SelectDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SelectDialog(QWidget *parent = 0);
	~SelectDialog();
	bool loadImage(const QString &path);

private:
	Ui::SelectDialog *ui;
	SelectScene* selectScene;
	QImage texture;

private slots:
	void doneSelecting();
signals:
	void rectSelected(int x1, int y1, int x2, int y2);
public slots:
	void selectRect(int x1, int y1, int x2, int y2);
};

#endif // SELECTDIALOG_H
