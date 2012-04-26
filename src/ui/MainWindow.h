#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "PageInterface.h"
#include "ActivitiesPage.h"
#include "StartPage.h"
#include "PCAPage.h"
#include "SOMPage.h"
#include "KMeansPage.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
	void setContent(IPage *page);

private:
    Ui::MainWindow *ui;
	ActivitiesPage activitiesPage;
	StartPage startPage;
	SOMPage somPage;
	KMeansPage kmeansPage;
	PCAPage pcaPage;
};

#endif // MAINWINDOW_H
