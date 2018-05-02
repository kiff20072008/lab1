#include"Lagrange.h"
double phi(int k, double z, double* x, int n)
{
	double res = 1;
	for (int i = 0; i < k; ++i)
	{
		res *= (z - x[i]) / (x[k] - x[i]);
	}
	for (int i = k + 1; i < n; ++i)
	{
		res *= (z - x[i]) / (x[k] - x[i]);
	}
	return res;
}

double Lagraunge(double z, double* x, double *y, int n)
{
	double s = 0;
	for (int k = 0; k < n; ++k)
	{
		s += y[k] * phi(k, z, x, n);
	}
	return s;
}
