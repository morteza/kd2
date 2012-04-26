#include "SideBarLabel.h"
#include "ui_SideBarLabel.h"
#include <iostream>

SideBarLabel::SideBarLabel(PageInterface *page, SideBar *parent) :
	ui(new Ui::SideBarLabel),
	bar(parent)
{
    ui->setupUi(this);

	// Set the palette.
	QPalette palette = this->palette();
	QColor whiteColor(200, 200, 200);
	QColor blackColor(0, 0, 0);
	palette.setColor(QPalette::Base, whiteColor);
	palette.setColor(QPalette::HighlightedText, blackColor);
	this->setPalette(palette);
	ui->titleLabel->setForegroundRole(this->palette().Base);
	ui->hintLabel->setForegroundRole(this->palette().Base);

	this->page = page;

	ui->titleLabel->setText(page->title());
	ui->iconLabel->setPixmap(page->icon().pixmap(24,24));
	ui->hintLabel->setText(page->hint());
}

SideBarLabel::~SideBarLabel()
{
    delete ui;
}

void SideBarLabel::setSelected(bool selected)
{
	if(isEnabled())
	{
		if(selected)
		{
			this->setAutoFillBackground(true);
			ui->titleLabel->setForegroundRole(this->palette().HighlightedText);
			ui->hintLabel->setForegroundRole(this->palette().HighlightedText);
		}else
		{			
			this->setAutoFillBackground(false);
			ui->titleLabel->setForegroundRole(this->palette().Base);
			ui->hintLabel->setForegroundRole(this->palette().Base);
		}
		this->repaint();
	}else{
	}

}

PageInterface *SideBarLabel::getPage()
{
	return this->page;
}

void SideBarLabel::mousePressEvent(QMouseEvent *ev)
{
	//QLabel::mousePressEvent(ev);
	ev->accept();

	if ( this->isEnabled())
	{
		emit clicked(this);
	}
}
