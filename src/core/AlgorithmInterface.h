#ifndef ALGORITHMINTERFACE_H
#define ALGORITHMINTERFACE_H

#include <QThread>
#include "ui/PageInterface.h"
#include "ui/ActivitiesPage.h"
#include "DatasetInterface.h"

/*! Algorithm represents an executable entity on data items, to extract
  desired knowledge from dataset. Each algorithm is a thread.
  **/

class AlgorithmInterface : public QThread
{
public:
        virtual ~AlgorithmInterface() = 0;
	//! initialize the algorithm based on the provided dataset and settings before running the algorithm.
        virtual void initialize(DatasetInterface &dataset, QSettings *settings) const = 0;
	//! main codes for the algorithm
        virtual void execute() const = 0;
	//! Provides IPage to show progress of algorithm execution
        virtual IPage *page() const = 0;
	//! Provides the algorithm with Activity page of Main Window to show progress, log , ...
        virtual void setActivitiesPage(ActivitiesPage *activitiesPage) const = 0;
	//! if execution of algorithm is complete and results are ready to be used
        virtual bool isKnowledgeReady() const = 0;
};

Q_DECLARE_INTERFACE(AlgorithmInteface, "kd-lads.AlgorithmInterface/2.0")

#endif // ALGORITHMINTERFACE_H
