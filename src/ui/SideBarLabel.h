#ifndef SIDEBARLABEL_H
#define SIDEBARLABEL_H

#include <QWidget>
#include <QMouseEvent>
#include "PageInterface.h"

class SideBar;

namespace Ui {
    class SideBarLabel;
}

class SideBarLabel : public QWidget
{
    Q_OBJECT

public:
        explicit SideBarLabel(PageInterface *page = 0, SideBar *parent = 0);
    ~SideBarLabel();
        PageInterface *getPage();
	void setSelected(bool selected);

signals:
	void clicked(SideBarLabel *label);

protected:
	void mousePressEvent(QMouseEvent *);

private:
    Ui::SideBarLabel *ui;
        PageInterface *page;
	SideBar *bar;
};

#endif // SIDEBARLABEL_H
