#include "Communicator.h"

Communicator::Communicator(int argc, char *argv[])
{
	int initFlag;
	MPI_Initialized(&initFlag);

	if (!initFlag)
	{
		MPI_Init(&argc, &argv);
		MPI_Comm_rank(MPI_COMM_WORLD, &m_rank);
		MPI_Comm_size(MPI_COMM_WORLD, &m_size);
	}
}

Communicator::~Communicator()
{
	int finishFlag;
	MPI_Initialized(&finishFlag);

	if (!finishFlag)
	{
		MPI_Finalize();
	}
}

int Communicator::size()
{
	return m_size;
}

int Communicator::rank()
{
	return m_rank;
}

void Communicator::sendDataset(IDataset *dataset, int to)
{

}
IDataset* Communicator::receiveDataset(int from)
{
	return 0;
}

void Communicator::sendData(std::vector<double> data, int to)
{

}
std::vector<double> Communicator::receiveData(int from)
{
	return std::vector<double>();
}

void Communicator::sendCommand(MPICommand cmd, int to)
{

}

MPICommand Communicator::receiveCommand(int from)
{
	return NULL_COMMAND;
}

void Communicator::sendString(std::string cmd, int to)
{

}

std::string Communicator::receiveString(int from)
{
	return "";
}

Matrix* Communicator::receiveMatrix(int from)
{
    return 0;
}

void Communicator::sendMatrix(Matrix *matrix, int to)
{

}

Vector* Communicator::receiveVector(int from)
{
    return 0;
}

void Communicator::sendVector(Vector *vector, int to)
{

}
