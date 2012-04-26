#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "core/IDataset.h"
#include "core/KD2Constants.h"
#include "math/Matrix.h"
#include "math/Vector.h"
#include <string>
#include <mpi.h>

class Matrix;
class Vector;

class Communicator
{
public:
	Communicator(int argc, char *argv[]);
	~Communicator();
	int rank();
	int size();

	void sendMatrix(Matrix *matrix, int to = KD2_MPI_BCAST);
	Matrix* receiveMatrix(int from = KD2_MPI_BCAST);

	void sendVector(Vector *vector, int to = KD2_MPI_BCAST);
	Vector* receiveVector(int from = KD2_MPI_BCAST);

	void sendDataset(IDataset *dataset, int to = KD2_MPI_BCAST);
	IDataset* receiveDataset(int from = KD2_MPI_BCAST);

	void sendData(std::vector<double> data, int to = KD2_MPI_BCAST);
	std::vector<double> receiveData(int from = KD2_MPI_BCAST);

	void sendCommand(MPICommand cmd, int to = KD2_MPI_BCAST);
	MPICommand receiveCommand(int from = KD2_MPI_BCAST);

	void sendString(std::string cmd, int to = KD2_MPI_BCAST);
	std::string receiveString(int from = KD2_MPI_BCAST);


private:
	int m_rank, m_size;
};

#endif // COMMUNICATOR_H
