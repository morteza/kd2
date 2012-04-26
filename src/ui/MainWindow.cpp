#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ActivitiesPage.h"
#include "StartPage.h"
#include "SOMPage.h"
#include "KMeansPage.h"
#include "PCAPage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::MainWindow),
	activitiesPage(),
	startPage(),
	somPage(),
	pcaPage(),
	kmeansPage()
{
    ui->setupUi(this);

        connect(ui->sidebar, SIGNAL(selectionChanged(PageInterface*)), this, SLOT(setContent(PageInterface*)));

	ui->sidebar->addPage(&startPage);
	ui->sidebar->addPage(&somPage);
	ui->sidebar->addPage(&kmeansPage);
	ui->sidebar->addPage(&pcaPage);


	ui->sidebar->addPage(&activitiesPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setContent(PageInterface *page)
{
	if (ui->content->widget())
		delete ui->content->widget();
	ui->content->setWidget(page->content(ui->content));
	this->setMinimumWidth(ui->sidebar->minimumWidth() + ui->content->widget()->minimumWidth() + 50);
	this->setMinimumHeight(ui->sidebar->minimumHeight() + ui->content->widget()->minimumHeight() + 50);
}
