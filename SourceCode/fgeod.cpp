// Source of Equations (22.04.2024): 
// https://itp.uni-frankfurt.de/~hanauske/VARTC/VARTC_2023/GeodKerrII_2023.ipynb
#ifndef FGEOD_CPP
#define FGEOD_CPP

#include<boost/numeric/ublas/vector.hpp>
#include<boost/numeric/ublas/io.hpp>
#include<iostream>
#include<string>
#include<cmath>

using namespace boost::numeric::ublas;

template<float &a> void F(const double t, const vector<double>& x, vector<double>& res) {

	double y_1, y_2, y_3, y_4, y_5, y_6, theta, M;
	theta = 3.1415/2;
	M = 1;
	if(a<0 or a>1) {
		std::cout << "a ist " << a << std::endl;
		std::cerr << "a muss zwischen 0 und 1 liegen" << std::endl;
		return;
	}
	//std::cout << "a " << a << std::endl;
	y_1 = x[0];  // t
	y_2 = x[1];  // r
	y_3 = x[2];  // phi
	y_4 = x[3];  // dt
	y_5 = x[4];  // dr
	y_6 = x[5];  // dphi
	
	// if the radius is smaller than the event horizon return 0 (i.e. no change in y_i)
	if(y_2 < (M + sqrt((M - a)*(M + a)))) {
		//std::cout << "inside event horizon\n";
		res[0] = 0;
		res[1] = 0;
		res[2] = 0;
		res[3] = 0;
		res[4] = 0;
		res[5] = 0;
		return;
	}

	res[0] = x[3];
	res[1] = x[4];
	res[2] = x[5];
	
	res[3] = 2*M*y_5*(pow(a, 3)*y_6 - pow(a, 2)*y_4 + 3*a*pow(y_2, 2)*y_6 - pow(y_2, 2)*y_4)/(pow(y_2, 2)*(-2*M*y_2 + pow(a, 2) + pow(y_2, 2)));
	
	res[4] = (2*pow(M, 2)*y_2*pow(-2*M*y_2 + pow(a, 2) + pow(y_2, 2), 3)*(pow(a, 2)*pow(y_6, 2) - 2*a*y_4*y_6 + pow(y_4, 2)) + M*pow(a, 2)*pow(-2*M*y_2 + pow(a, 2) + pow(y_2, 2), 3)*(-pow(a, 2)*pow(y_6, 2) + 2*a*y_4*y_6 - pow(y_4, 2)) + M*pow(y_2, 2)*pow(-2*M*y_2 + pow(a, 2) + pow(y_2, 2), 3)*(-pow(a, 2)*pow(y_6, 2) + 2*a*y_4*y_6 - pow(y_4, 2)) - pow(a, 2)*pow(y_2, 3)*pow(y_5, 2)*pow(-2*M*y_2 + pow(a, 2) + pow(y_2, 2), 2) + pow(a, 2)*pow(y_2, 3)*pow(y_6, 2)*pow(-2*M*y_2 + pow(a, 2) + pow(y_2, 2), 3) + pow(y_2, 4)*pow(y_5, 2)*(2*M - y_2)*pow(-2*M*y_2 + pow(a, 2) + pow(y_2, 2), 2) + pow(y_2, 4)*pow(y_5, 2)*(-4*pow(M, 3)*pow(y_2, 2) + 4*pow(M, 2)*pow(a, 2)*y_2 + 8*pow(M, 2)*pow(y_2, 3) - M*pow(a, 4) - 6*M*pow(a, 2)*pow(y_2, 2) - 5*M*pow(y_2, 4) + pow(a, 4)*y_2 + 2*pow(a, 2)*pow(y_2, 3) + pow(y_2, 5)) + pow(y_2, 4)*pow(y_6, 2)*(-2*M + y_2)*pow(-2*M*y_2 + pow(a, 2) + pow(y_2, 2), 3))/(pow(y_2, 4)*pow(-2*M*y_2 + pow(a, 2) + pow(y_2, 2), 3));
	
	res[5] = 2*y_5*(M*pow(a, 2)*y_6 - M*a*y_4 + 2*M*pow(y_2, 2)*y_6 - pow(y_2, 3)*y_6)/(pow(y_2, 2)*(-2*M*y_2 + pow(a, 2) + pow(y_2, 2)));
	
} 

double get_dt0(double a, double r, double dr, double dphi, double M=1) {
	double wert = (2*M*a*dphi*(4*pow(M, 2)*r - 2*M*pow(a, 2) - 4*M*pow(r, 2) + pow(a, 2)*r + pow(r, 3)) + sqrt(r*(-2*M*r + pow(a, 2) + pow(r, 2))*(4*pow(M, 2)*pow(dphi, 2)*pow(r, 3) + 4*pow(M, 2)*r - 4*M*pow(a, 2)*pow(dphi, 2)*pow(r, 2) - 2*M*pow(a, 2) - 4*M*pow(dphi, 2)*pow(r, 4) - 2*M*pow(dr, 2)*pow(r, 2) - 4*M*pow(r, 2) + pow(a, 4)*pow(dphi, 2)*r + 2*pow(a, 2)*pow(dphi, 2)*pow(r, 3) + pow(a, 2)*r + pow(dphi, 2)*pow(r, 5) + pow(dr, 2)*pow(r, 3) + pow(r, 3)))*(2*M - r))/((2*M - r)*(4*pow(M, 2)*r - 2*M*pow(a, 2) - 4*M*pow(r, 2) + pow(a, 2)*r + pow(r, 3)));
	return wert;
}

#endif
