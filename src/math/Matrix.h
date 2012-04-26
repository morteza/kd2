#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"
#include "parallel/Communicator.h"

class Communicator;

class Matrix
{
public:
	Matrix(long rows, long cols);
	~Matrix();

	void assignRow(long row, Vector *vector);
	Matrix times(Matrix *matrix);
	Vector times(Vector *vector);
	//! parallel product using communicator passed as an argument
	Vector times(Vector *vector, Communicator *comm);
	Vector timesSquared(Vector *vector);

	double getValue(long row, long col);

	long cols;
	long rows;
	double **values;
};

#endif // MATRIX_H
