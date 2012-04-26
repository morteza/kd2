#ifndef STARTPAGE_H
#define STARTPAGE_H

#include "PageInterface.h"
#include "ui_StartPage.h"

class StartPage : public PageInterface
{
	Q_OBJECT
public:
	StartPage();
	~StartPage();
	QString title();
	QString hint();
	QIcon icon();
	QWidget* content(QWidget* parent = 0);

public slots:
	void on_browseForDatasetBtn_clicked();

private:
	Ui::StartPageWidget *ui;
};

#endif // STARTPAGE_H
