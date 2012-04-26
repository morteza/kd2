#include <iostream>
#include <cmath>

using namespace std;

void test_svd();
void svd(double **&A, int rows, int cols, double **&U, double *&s, double **&V);
void pca(double **&A, int rows, int cols, double **&PCs);

int main(int argc, char *argv[])
{

	test_svd();


	return 0;
}

/**
 * sqrt(a^2 + b^2) without under/overflow.
 */
double hypot(double a, double b) {
  double r;
  if (abs(a) > abs(b)) {
	r = b/a;
	r = abs(a)*sqrt(1+r*r);
  } else if (b != 0) {
	r = a/b;
	r = abs(b)*sqrt(1+r*r);
  } else {
	r = 0.0;
  }
  return r;
}

/**
 * Effective numerical matrix rank
 * \return Number of non-negligible singular values
 */
int rank(double *s, int s_length, int rows, int cols) {
  double eps = pow(2.0,-52.0);
  double tol = max(rows ,cols)*s[0]*eps;
  int r = 0;
  for (int i = 0; i < s_length; i++) {
	if (s[i] > tol) {
	  r++;
	}
  }
  return r;
}

void svd(double **&A, int rows, int cols, double **&U, double *&s, double **&V)
{

	// Initialized variables
	int nu = min(rows,cols);
	s = new double[min(rows+1,cols)];
	U = new double*[rows];
	for (int i=0;i<rows;i++) U[i] = new double[nu];
	V = new double*[cols];
	for (int i=0;i<cols;i++) V[i] = new double[cols];

	double *e = new double [cols];
	double *work = new double [rows];

	// Reduce A to bidiagonal form, storing the diagonal elements
	// in s and the super-diagonal elements in e.

	int nct = min(rows-1,cols);
	int nrt = max(0,min(rows, cols-2));

	for (int k = 0; k < max(nct,nrt); k++) {
	  if (k < nct) {

		// Compute the transformation for the k-th column and
		// place the k-th diagonal in s[k].
		// Compute 2-norm of k-th column without under/overflow.
		s[k] = 0;
		for (int i = k; i < rows; i++) {
		  s[k] = hypot(s[k],A[i][k]);
		}
		if (s[k] != 0.0) {
		  if (A[k][k] < 0.0) {
			s[k] = -s[k];
		  }
		  for (int i = k; i < rows; i++) {
			A[i][k] /= s[k];
		  }
		  A[k][k] += 1.0;
		}
		s[k] = -s[k];
	  }

	  for (int j = k+1; j < cols; j++) {
		if ((k < nct) & (s[k] != 0.0))  {

		  // Apply the transformation.

		  double t = 0;
		  for (int i = k; i < rows; i++) {
			t += A[i][k]*A[i][j];
		  }
		  t = -t/A[k][k];
		  for (int i = k; i < rows; i++) {
			A[i][j] += t*A[i][k];
		  }
		}

		// Place the k-th row of A into e for the
		// subsequent calculation of the row transformation.

		e[j] = A[k][j];
	  }

	  if (k < nrt) {

		// Compute the k-th row transformation and place the
		// k-th super-diagonal in e[k].
		// Compute 2-norm without under/overflow.

		e[k] = 0;
		for (int i = k+1; i < cols; i++) {
		  e[k] = hypot(e[k],e[i]);
		}
		if (e[k] != 0.0) {
		  if (e[k+1] < 0.0) {
			e[k] = -e[k];
		  }
		  for (int i = k+1; i < cols; i++) {
			e[i] /= e[k];
		  }
		  e[k+1] += 1.0;
		}
		e[k] = -e[k];
		if ((k+1 < rows) & (e[k] != 0.0)) {

		  // Apply the transformation.

		  for (int i = k+1; i < rows; i++) {
			work[i] = 0.0;
		  }
		  for (int j = k+1; j < cols; j++) {
			for (int i = k+1; i < rows; i++) {
			  work[i] += e[j]*A[i][j];
			}
		  }
		  for (int j = k+1; j < cols; j++) {
			double t = -e[j]/e[k+1];
			for (int i = k+1; i < rows; i++) {
			  A[i][j] += t*work[i];
			}
		  }
		}

		for (int i = k+1; i < cols; i++) {
			V[i][k] = e[i];
		}
	  }
	}

	// Set up the final bidiagonal matrix or order p.

	int p = min(cols,rows+1);
	if (nct < cols) {
	  s[nct] = A[nct][nct];
	}
	if (rows < p) {
	  s[p-1] = 0.0;
	}
	if (nrt+1 < p) {
	  e[nrt] = A[nrt][p-1];
	}
	e[p-1] = 0.0;

	// Generate V.

	for (int k = cols-1; k >= 0; k--) {
	  if ((k < nrt) & (e[k] != 0.0)) {
		for (int j = k+1; j < nu; j++) {
		  double t = 0;
		  for (int i = k+1; i < cols; i++) {
			 t += V[i][k]*V[i][j];
		  }
		  t = -t/V[k+1][k];
		  for (int i = k+1; i < cols; i++) {
			V[i][j] += t*V[i][k];
		  }
		}
	  }
	  for (int i = 0; i < cols; i++) {
		V[i][k] = 0.0;
	  }
	  V[k][k] = 1.0;
	}

	// Main iteration loop for the singular values.

	int pp = p-1;
	int iter = 0;
	double eps = pow(2.0,-52.0);
	double tiny = pow(2.0,-966.0);
	while (p > 0) {
	  int k,kase;

	  for (k = p-2; k >= -1; k--) {
		if (k == -1) {
		  break;
		}
		if (abs(e[k]) <= tiny + eps*(abs(s[k]) + abs(s[k+1]))) {
		  e[k] = 0.0;
		  break;
		}
	  }
	  if (k == p-2) {
		kase = 4;
	  } else {
		int ks;
		for (ks = p-1; ks >= k; ks--) {
		  if (ks == k) {
			break;
		  }
		  double t = (ks != p ? abs(e[ks]) : 0.0) + (ks != k+1 ? abs(e[ks-1]) : 0.0);
		  if (abs(s[ks]) <= tiny + eps*t)  {
			s[ks] = 0.0;
			break;
		  }
		}
		if (ks == k) {
		  kase = 3;
		} else if (ks == p-1) {
		  kase = 1;
		} else {
		  kase = 2;
		  k = ks;
		}
	  }
	  k++;

	  // Perform the task indicated by kase.
	  // kase = 1     if s(p) and e[k-1] are negligible and k<p
	  // kase = 2     if s(k) is negligible and k<p
	  // kase = 3     if e[k-1] is negligible, k<p, and
	  //              s(k), ..., s(p) are not negligible (qr step).
	  // kase = 4     if e(p-1) is negligible (convergence).
		switch (kase) {
		case 1: {
			double f = e[p-2];
			e[p-2] = 0.0;
			for (int j = p-2; j >= k; j--) {
			  double t = hypot(s[j],f);
			  double cs = s[j]/t;
			  double sn = f/t;
			  s[j] = t;
			  if (j != k) {
				f = -sn*e[j-1];
				e[j-1] = cs*e[j-1];
			  }
			  for (int i = 0; i < cols; i++) {
				t = cs*V[i][j] + sn*V[i][p-1];
				V[i][p-1] = -sn*V[i][j] + cs*V[i][p-1];
				V[i][j] = t;
			  }
			}
		}
			break;
		case 2: {
			double f = e[k-1];
			e[k-1] = 0.0;
			for (int j = k; j < p; j++) {
			  double t = hypot(s[j],f);
			  double cs = s[j]/t;
			  double sn = f/t;
			  s[j] = t;
			  f = -sn*e[j];
			  e[j] = cs*e[j];
			}
		}
			break;
		case 3: {
				// Calculate the shift.

				 double scale = max(max(max(max(abs(s[p-1]), abs(s[p-2])), abs(e[p-2])),abs(s[k])),abs(e[k]));
				 double sp = s[p-1]/scale;
				 double spm1 = s[p-2]/scale;
				 double epm1 = e[p-2]/scale;
				 double sk = s[k]/scale;
				 double ek = e[k]/scale;
				 double b = ((spm1 + sp)*(spm1 - sp) + epm1*epm1)/2.0;
				 double c = (sp*epm1)*(sp*epm1);
				 double shift = 0.0;
				 if ((b != 0.0) | (c != 0.0)) {
				   shift = sqrt(b*b + c);
				   if (b < 0.0) {
					 shift = -shift;
				   }
				   shift = c/(b + shift);
				 }
				 double f = (sk + sp)*(sk - sp) + shift;
				 double g = sk*ek;

				 // Chase zeros.

				 for (int j = k; j < p-1; j++) {
				   double t = hypot(f,g);
				   double cs = f/t;
				   double sn = g/t;
				   if (j != k) {
					 e[j-1] = t;
				   }
				   f = cs*s[j] + sn*e[j];
				   e[j] = cs*e[j] - sn*s[j];
				   g = sn*s[j+1];
				   s[j+1] = cs*s[j+1];
				   for (int i = 0; i < cols; i++) {
					  t = cs*V[i][j] + sn*V[i][j+1];
					  V[i][j+1] = -sn*V[i][j] + cs*V[i][j+1];
					  V[i][j] = t;
				   }
				   t = hypot(f,g);
				   cs = f/t;
				   sn = g/t;
				   s[j] = t;
				   f = cs*e[j] + sn*s[j+1];
				   s[j+1] = -sn*e[j] + cs*s[j+1];
				   g = sn*e[j+1];
				   e[j+1] = cs*e[j+1];
				 }
				 e[p-2] = f;
				 iter = iter + 1;
		}
			break;
		case 4:{

				// Make the singular values positive.

				if (s[k] <= 0.0) {
				  s[k] = (s[k] < 0.0 ? -s[k] : 0.0);
				  for (int i = 0; i <= pp; i++) {
					  V[i][k] = -V[i][k];
				  }
				}

				// Order the singular values.

				while (k < pp) {
				  if (s[k] >= s[k+1]) {
					break;
				  }
				  double t = s[k];
				  s[k] = s[k+1];
				  s[k+1] = t;
				  if (k < cols-1) {
					for (int i = 0; i < cols; i++) {
					  t = V[i][k+1];
					  V[i][k+1] = V[i][k];
					  V[i][k] = t;
					}
				  }
				  k++;
				}
				iter = 0;
				p--;
		}
			break;
		} /// END-SWITCH (KASE)

	} /// END-WHILE

}


void test_svd()
{
	double **A = new double*[6];
	for (int i=0;i<6;i++) A[i] = new double[5];
	A[0][0] = 1.0;
	A[0][1] = 1.0;
	A[0][2] = 1.0;
	A[0][3] = 1.0;
	A[0][4] = 1.0;

	A[1][0] = 0.0;
	A[1][1] = 0.7578582801241234;
	A[1][2] = 0.8705505614977934;
	A[1][3] = 0.9440875104854797;
	A[1][4] = 1.0;

	A[2][0] = 0.0;
	A[2][1] = 0.5743491727526943;
	A[2][2] = 0.7578582801241234;
	A[2][3] = 0.8913012274546708;
	A[2][4] = 1.0;

	A[3][0] = 0.0;
	A[3][1] = 0.4352752672614163;
	A[3][2] = 0.6597539444834084;
	A[3][3] = 0.841466353313137;
	A[3][4] = 1.0;

	A[4][0] = 0.0;
	A[4][1] = 0.3298769722417042;
	A[4][2] = 0.5743491727526943;
	A[4][3] = 0.7944178780622027;
	A[4][4] = 1.0;

	A[5][0] = 0.0;
	A[5][1] = 0.25;
	A[5][2] = 0.5;
	A[5][3] = 0.75;
	A[5][4] = 1.0;

	double **U;
	double *s;
	double **V;
	cout << "OK! starting ... " << endl;
	svd(A, 6, 5, U, s, V);


	int cols = 5;
	cout << "Results: V[][] = " << endl;
	for (int i = 0 ; i< cols; i++) {
		for ( int j =0 ; j< cols; j++)
		{
			cout << V[i][j] << '\t' ;
		}
		cout << endl;
	}
	cout << "S[] = " << endl;
	for (int i = 0 ; i< cols; i++) {
		cout << s[i] << '\t' ;
	}

}

void pca(double **&A, int rows, int cols, double **&PCs)
{
	//TODO: normalize A
	//TODO: construct matrix Y=A^T / SQRT(rows-1)
	//TODO: PC = matrix V of svd(Y)
}
