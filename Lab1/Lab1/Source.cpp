#include <iostream>
#include <iomanip>
#include "Lagrange.h"
#include "Quanc8.h"

#define SIZE_OF_ARRAY 11
using namespace std;

double funcf_x(double x)
{
	if (x == 0)
		return 0;
	return ((1 - cos(x))/x);
}

void printLine()
{
	for (int i = 0; i < 60; ++i)
	{
		cout << "-";
	}
	cout << endl;
}
int main()
{
	double point_arr_x[SIZE_OF_ARRAY],point_arr_x_2[SIZE_OF_ARRAY];
	double temp_x[SIZE_OF_ARRAY + 1], temp_y[SIZE_OF_ARRAY + 1];
	double point_arr_lagrange[SIZE_OF_ARRAY];
	double point_arr_spline[SIZE_OF_ARRAY];
	double point_arr_quanc8[SIZE_OF_ARRAY],	point_arr_quanc8_2[SIZE_OF_ARRAY];
	double B[SIZE_OF_ARRAY+1], C[SIZE_OF_ARRAY+1], D[SIZE_OF_ARRAY+1];
	double  errest  , flag;
	int  nfe ;
	double a = 2.0;

	//Get quanc for x=2 to x=3
	for (int i = 0; i < SIZE_OF_ARRAY; ++i, a += 0.1)
	{
		point_arr_x[i] = a;
		quanc8(funcf_x,0, a, 0.0, 1.0e-10, point_arr_quanc8[i], errest,nfe,flag);
		
	}

	//prepare new arr for spline 
	temp_x[0] = 0;
	temp_y[0] = 0;
	for (int i = 0; i < SIZE_OF_ARRAY; ++i)
	{
		temp_x[i + 1] = point_arr_x[i];
		temp_y[i + 1] = point_arr_quanc8[i];
	}
	//spline 
	spline(SIZE_OF_ARRAY, temp_x, temp_y, B, C, D);

	//For x=2 to 3 print Quanc lagrange and spline 
	cout << "   X     Quanc8     Flag  Lagrange   Spline" << endl;
	printLine();
	for (int i = 0; i < SIZE_OF_ARRAY; ++i)
	{
		point_arr_spline[i] = seval(SIZE_OF_ARRAY, &point_arr_x[i], temp_x, temp_y, B, C, D);
		point_arr_lagrange[i] = Lagraunge(point_arr_x[i], point_arr_x, point_arr_quanc8, SIZE_OF_ARRAY);
		cout << setw(4) << point_arr_x[i] << "     " << setw(8) << point_arr_quanc8[i] << "   " << setw(4) << flag << "  " << setw(6) << point_arr_lagrange[i] << "   " << setw(8) << point_arr_spline[i] << endl;
	}
	cout << endl;
	
	//Quanc for x=2.05 to 2.95
	a = 2.05;
	for (int i = 0; i < 10; ++i,a += 0.1)
	{
		point_arr_x_2[i] = a;
		quanc8(funcf_x, 0, a, 0.0, 1.0e-10, point_arr_quanc8_2[i], errest, nfe, flag);		
	}

	//For x=2.05 to 2.95 print Quanc lagrange and spline 	
	cout << "X       Quanc8  Lagrange     Spline  Accuracy L     Accuracy S" << endl;
	printLine();
	for (int i = 0; i < 10; ++i)
	{
		point_arr_spline[i] = seval(SIZE_OF_ARRAY, &point_arr_x_2[i], temp_x, temp_y, B, C, D);
		point_arr_lagrange[i] = Lagraunge(point_arr_x_2[i], point_arr_x, point_arr_quanc8, SIZE_OF_ARRAY);
		cout << setw(4) << point_arr_x_2[i] << "  " << setw(8) << point_arr_quanc8_2[i] << "  " << setw(8) << point_arr_lagrange[i]   << "   " << setw(8) << point_arr_spline[i] << "  " << setw(10) << point_arr_quanc8_2[i]-point_arr_lagrange[i] << "   " << point_arr_quanc8_2[i]- point_arr_spline[i] << endl;
	}

	system("pause");
	return 0;
}