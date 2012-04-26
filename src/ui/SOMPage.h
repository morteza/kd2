#ifndef SOMPAGE_H
#define SOMPAGE_H

#include "PageInterface.h"
#include "ui_SOMPage.h"

class SOMPage : public PageInterface
{
	Q_OBJECT
public:
	SOMPage();
	~SOMPage();
	QString title();
	QString hint();
	QIcon icon();
	QWidget* content(QWidget* parent = 0);

public slots:

private:
	Ui::SOMPageWidget *ui;
};

#endif // SOMPAGE_H
