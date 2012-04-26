#ifndef PAGEINTERFACE_H
#define PAGEINTERFACE_H

#include <QObject>
#include <QString>
#include <QIcon>
#include <QWidget>

/*!
  \class PageInterface
  \brief Abstract class to add a page to the sidebar of KD2
  */
class PageInterface : public QObject
{
public:
        virtual ~PageInterface() {}
	//! Provides title of the page to be show in the sidebar
	virtual QString title() = 0;
	//! Provides a small text to be show as a hint for this page
	virtual QString hint() = 0;
	//! Provides icon for this page
	virtual QIcon icon() = 0;
	//! Provides contents of this page to be shown when this page is selected
	virtual QWidget* content(QWidget* parent = 0) = 0;
};

Q_DECLARE_INTERFACE(PageInterface, "kd-lads.PageInterface/2.0")


#endif // PAGEINTERFACE_H
