#include "SOMPage.h"
#include <QFileDialog>

SOMPage::SOMPage()
{
	ui = new Ui::SOMPageWidget();
}

SOMPage::~SOMPage()
{
	delete ui;
}

QString SOMPage::hint()
{
	return QString("Self-Organization Map");
}

QString SOMPage::title()
{
	return QString("Parallel SOM");
}

QIcon SOMPage::icon()
{
	return QIcon(":/resources/som_page.png");
}

QWidget *SOMPage::content(QWidget* parent)
{
	QWidget *w = new QWidget(parent);
	ui->setupUi(w);
	return w;
}
