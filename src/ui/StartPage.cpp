#include "StartPage.h"
#include <QFileDialog>

StartPage::StartPage()
{
	ui = new Ui::StartPageWidget();
}

StartPage::~StartPage()
{
	delete ui;
}

QString StartPage::hint()
{
	return QString("General Configurations");
}

QString StartPage::title()
{
	return QString("Start");
}

QIcon StartPage::icon()
{
	return QIcon(":/resources/start_page.png");
}

QWidget *StartPage::content(QWidget* parent)
{
	QWidget *w = new QWidget(parent);
	ui->setupUi(w);
	connect(ui->browseForDatasetBtn, SIGNAL(clicked()), this, SLOT(on_browseForDatasetBtn_clicked()));
	return w;
}

void StartPage::on_browseForDatasetBtn_clicked()
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
