#ifndef PCAPAGE_H
#define PCAPAGE_H

#include "PageInterface.h"
#include "ui_PCAPage.h"

class PCAPage : public PageInterface
{
	Q_OBJECT
public:
	PCAPage();
	~PCAPage();
	QString title();
	QString hint();
	QIcon icon();
	QWidget* content(QWidget* parent = 0);

public slots:
	void on_browseForDatasetBtn_clicked();

private:
	Ui::PCAPageWidget *ui;
};

#endif // PCAPAGE_H
