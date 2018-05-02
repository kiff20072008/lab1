#ifndef _QUANC8_H_
#define _QUANC8_H_

#include <cmath>

void quanc8(double(*fun)(double), double a, double b,
	double abserr, double relerr,
	double& result, double& errest, int& nofun, double& flag);
void spline(int n, double * x, double * y, double * b, double * c, double * d);

double seval(int n, double * u, double * x, double * y, double * b, double * c, double * d);
#endif