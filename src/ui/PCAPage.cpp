#include "PCAPage.h"
#include <QFileDialog>

PCAPage::PCAPage()
{
	ui = new Ui::PCAPageWidget();
}

PCAPage::~PCAPage()
{
	delete ui;
}

QString PCAPage::hint()
{
	return QString("Parallel PCA Algorithm");
}

QString PCAPage::title()
{
	return QString("Parallel PCA");
}

QIcon PCAPage::icon()
{
	return QIcon(":/resources/pca_page.png");
}

QWidget *PCAPage::content(QWidget* parent)
{
	QWidget *w = new QWidget(parent);
	ui->setupUi(w);
	connect(ui->browseForDatasetBtn, SIGNAL(clicked()), this, SLOT(on_browseForDatasetBtn_clicked()));
	return w;
}

void PCAPage::on_browseForDatasetBtn_clicked()
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
