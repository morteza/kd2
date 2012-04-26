#include <iostream>
#include <mpi.h>

#include <QtGui>
#include "ui/MainWindow.h"

using namespace std;

int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);
	int rank = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank ==0 )
	{
		QApplication a(argc, argv);
		MainWindow window;
		window.show();
		a.exec();
	}
	MPI_Finalize();
	return 0;
}
