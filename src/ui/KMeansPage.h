#ifndef KMEANSPAGE_H
#define KMEANSPAGE_H

#include "PageInterface.h"
#include "ui_KMeansPage.h"

class KMeansPage : public PageInterface
{
	Q_OBJECT
public:
	KMeansPage();
	~KMeansPage();
	QString title();
	QString hint();
	QIcon icon();
	QWidget* content(QWidget* parent = 0);

public slots:
	void on_browseForDatasetBtn_clicked();

private:
	Ui::KMeansPageWidget *ui;
};

#endif // KMEANSPAGE_H
