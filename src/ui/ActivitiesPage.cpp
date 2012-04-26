#include "ActivitiesPage.h"

ActivitiesPage::ActivitiesPage() :
	m_logInfoIcon(":/resources/green-dot.png"),
	m_logDebugIcon(":/resources/yellow-dot.png"),
	m_logErrorIcon(":/resources/red-dot.png")
{
	m_pageWidget = new Ui::ActivitiesPageWidget();
}

ActivitiesPage::~ActivitiesPage()
{
	delete m_pageWidget;
}

QString ActivitiesPage::hint()
{
	return QString("Current running activities");
}

QString ActivitiesPage::title()
{
	return QString("Activities");
}

QIcon ActivitiesPage::icon()
{
	return QIcon(":/resources/activities-page.png");
}

QWidget *ActivitiesPage::content(QWidget* parent)
{
	QWidget *w = new QWidget(parent);

	m_pageWidget->setupUi(w);

	return w;
}

void ActivitiesPage::clearLogs()
{
	m_pageWidget->logList->clear();
	logItems.clear();
}

void ActivitiesPage::log(QString logText, LogLevel level)
{
	QListWidgetItem *logItem = new QListWidgetItem();
	logItem->setText(logText);

	switch(level)
	{
	case INFORMATION:
		logItem->setIcon(m_logInfoIcon);
		break;
	case DEBUG:
		logItem->setIcon(m_logDebugIcon);
		break;
	case ERROR:
		logItem->setIcon(m_logErrorIcon);
		break;
	};

	m_pageWidget->logList->addItem(logItem);
	logItems.push_back(logItem);
}
