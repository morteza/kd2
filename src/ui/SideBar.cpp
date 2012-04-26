#include "SideBar.h"

SideBar::SideBar(QWidget *parent) :
	QFrame(parent)
{

	currentLabel = 0; // set to null

	labelLayout = new QVBoxLayout(this);
	labelLayout->setContentsMargins(0,0,0,0);
	labelLayout->setSpacing(0);
	setLayout(labelLayout);

}

SideBar::~SideBar()
{

}

QSize SideBar::sizeHint() const
{
	return QSize(200, ( pageLabels.size() + 1 ) * 50 + 200);
}

QSize SideBar::minimumSize() const
{
	return QSize(200, 200);
}

void SideBar::addPage(PageInterface *page)
{
	SideBarLabel *label = new SideBarLabel(page, this);
	label->connect(label, SIGNAL(clicked(SideBarLabel*)),this,SLOT(selectPage(SideBarLabel*)));
	pageLabels.append(label);
	if (label->getPage()->title().compare("Activities") == 0){
		QSpacerItem *spc = new QSpacerItem(40,40,QSizePolicy::Expanding,QSizePolicy::Expanding);
		this->labelLayout->addSpacerItem(spc);
		this->labelLayout->setAlignment(label, Qt::AlignBottom);
	}
	this->labelLayout->addWidget(label);
	if (label->getPage()->title().compare("Activities") == 0)
		this->labelLayout->setAlignment(label, Qt::AlignBottom);
	else
		this->labelLayout->setAlignment(label, Qt::AlignTop);
}

void SideBar::selectPage(SideBarLabel *label)
{
	if(currentLabel == label)
		return;
	if (currentLabel)
		currentLabel->setSelected(false);
	label->setSelected(true);
	currentLabel = label;
	if (label->isEnabled())
		emit selectionChanged(label->getPage());
}

void SideBar::paintEvent(QPaintEvent *event)
{
	event->accept();
}
