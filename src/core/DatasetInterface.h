#ifndef DATASETINTERFACE_H
#define DATASETINTERFACE_H

#include <vector>
#include <QObject>

/*! Abstract class which represents a set of data items. This class is extended by CSVDataset, MemoryDataset, etc.
  \class DatasetInterface
  **/
class DatasetInterface : QObject
{
public:
        virtual ~DatasetInterface();
	virtual void initialize() = 0;
	virtual double getFeature(int row, int dimension) = 0;
	virtual std::vector<double> getRow(int index) = 0;
	virtual int dimension() = 0;
	virtual int size() = 0;
	//! Extracts a subset of data items in form of a new Dataset.
        virtual DatasetInterface* subset(int offset, int size) = 0;
};

Q_DECLARE_INTERFACE(DatasetInterface, "kd-lads.DatasetInterface/2.0")

#endif // DATASETINTERFACE_H
