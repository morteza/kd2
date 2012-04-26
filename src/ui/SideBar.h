#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QFrame>
#include <QList>
#include <QPaintEvent>
#include <QSize>
#include <QVBoxLayout>
#include "MainWindow.h"
#include "PageInterface.h"
#include "SideBarLabel.h"

class SideBar : public QFrame
{
	Q_OBJECT
public:
	explicit SideBar(QWidget *parent = 0);
	~SideBar();
        void addPage(PageInterface *page);
	QSize sizeHint() const;
	QSize minimumSize() const;

signals:
        void selectionChanged(PageInterface *newPage);

public slots:
	void selectPage(SideBarLabel *label);

protected:
	void paintEvent(QPaintEvent *event);

private:
	QList<SideBarLabel*> pageLabels;
	SideBarLabel *currentLabel;
	QVBoxLayout *labelLayout;

};

#endif // SIDEBAR_H
