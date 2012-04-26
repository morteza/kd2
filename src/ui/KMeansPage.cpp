#include "KMeansPage.h"
#include <QFileDialog>

KMeansPage::KMeansPage()
{
	ui = new Ui::KMeansPageWidget();
}

KMeansPage::~KMeansPage()
{
	delete ui;
}

QString KMeansPage::hint()
{
	return QString("Parallel K-Means Algorithm");
}

QString KMeansPage::title()
{
	return QString("Parallel K-Means");
}

QIcon KMeansPage::icon()
{
	return QIcon(":/resources/kmeans_page.png");
}

QWidget *KMeansPage::content(QWidget* parent)
{
	QWidget *w = new QWidget(parent);
	ui->setupUi(w);
	connect(ui->browseForDatasetBtn, SIGNAL(clicked()), this, SLOT(on_browseForDatasetBtn_clicked()));
	return w;
}

void KMeansPage::on_browseForDatasetBtn_clicked()
{
	//TODO: show based on selected dataset type
	QFileDialog openDialog;
	openDialog.setFileMode(QFileDialog::Directory);
	openDialog.setOption(QFileDialog::ShowDirsOnly, true);
	QString dirPath;
	if(openDialog.exec())
	{
		dirPath = openDialog.selectedFiles().at(0);
		ui->lineEdit->setText(dirPath);
	}
}
