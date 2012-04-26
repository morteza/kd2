#ifndef ACTIVITIESPAGE_H
#define ACTIVITIESPAGE_H

#include "PageInterface.h"
#include "ui_ActivitiesPage.h";
#include "core/KD2Constants.h"
#include <vector>

class ActivitiesPage : public PageInterface
{
public:
	ActivitiesPage();
	~ActivitiesPage();
	QString title();
	QString hint();
	QIcon icon();
	QWidget* content(QWidget *parent = 0);

public slots:
	void log(QString logText, LogLevel level);
	void clearLogs();

private:
	Ui::ActivitiesPageWidget *m_pageWidget;
	QIcon m_logInfoIcon, m_logDebugIcon, m_logErrorIcon;
	std::vector<QListWidgetItem*> logItems;
};

#endif // ACTIVITIESPAGE_H
