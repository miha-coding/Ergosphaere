#include "solver.h"
#include "fgeod.cpp"
#include<boost/numeric/ublas/vector.hpp>
#include<boost/numeric/ublas/io.hpp>
#include<iostream>
#include<string>
#include<cmath>
#include<sstream>

#include<omp.h>

using namespace boost::numeric::ublas;


void different_a();
void different_r(float a);
void different_dphi(float a);
template<class T> void append(std::string &stringvar, T val);

int main() {
	float a = 0.95;
	//different_r(a);
	different_dphi(a);
	//different_a();  // ohne Parallelisierung
	return 0;
}

void different_r(float a) {
	static float cur = a;  // Must be static to hand over cur as a template parameter.

	float r_list[] = { 10, 8, 6, 4};
	int N = sizeof(r_list)/sizeof(float);	

	double dt0;
	double init[6];
	Solver tmp;
	
	
	
	#pragma omp parallel for private(dt0, init, tmp)
	for(int i=0; i<N; i++) {
		tmp.set_tEnd(40);
		tmp.set_N(5*pow(10,4));
		init[0] = 0.0;		// t_0
		init[1] = r_list[i];	// r_0
		init[2] = 0.0;		// phi_0
		// init[3] later
		init[4] = 0.0;		// dr_0
		init[5] = 0.0;		// dphi_0
		// Set dt0
		dt0 = get_dt0(cur, init[1], init[4], init[5]);
		init[3] = dt0;
		
		tmp.set_init_value(sizeof(init)/sizeof(double), init);

		std::cout << "Start with " << i << std::endl;
		tmp.setF(&F<cur>);
		std::string fileName("");
		fileName = "dat_r";
		append(fileName, r_list[i]);
		append(fileName, "_a");
		append(fileName, a);
		tmp.setFileName(fileName);
		tmp.solve();
		
		std::cout << "Finished " << i << std::endl;
	}
}

void different_dphi(float a) {
	static float cur = a;  // Must be static to hand over cur as a template parameter.

	float dphi_list[] = { -0.04, -0.03, -0.01, 0.01};
	int N = sizeof(dphi_list)/sizeof(float);	

	double dt0;
	double init[6];
	Solver tmp;
	
	
	
	#pragma omp parallel for private(dt0, init, tmp)
	for(int i=0; i<N; i++) {
		tmp.set_tEnd(100);
		tmp.set_N(5*pow(10,4));
		init[0] = 0.0;		// t_0
		init[1] = 5.0;		// r_0
		// init[3] later
		init[2] = 0.0;		// phi_0
		init[4] = 0.0;		// dr_0
		init[5] = dphi_list[i]; // dphi_0
		// Set dt0
		dt0 = get_dt0(cur, init[1], init[4], init[5]);
		init[3] = dt0;		// dt_0
		
		tmp.set_init_value(sizeof(init)/sizeof(double), init);

		std::cout << "Start with " << i << std::endl;
		tmp.setF(&F<cur>);
		std::string fileName("");
		fileName = "dat_dphi";
		append(fileName, dphi_list[i]);
		append(fileName, "_a");
		append(fileName, a);
		tmp.setFileName(fileName);
		tmp.solve();
		
		std::cout << "Finished " << i << std::endl;
	}
}

void different_a() {
	float a_list[] = {0.8, 0.90, 0.925, 0.950, 0.975};
	static float cur;  // Must be static to hand over cur as a template parameter.

	int N = sizeof(a_list)/sizeof(float);

	double dt0;
	
	double init[6];  // t0, r0, phi0, dt0, dr0, dphi0
	Solver tmp;
	
	// Does not work parallel (most likely since cur is static).
	//#pragma omp parallel for private(dt0, init, tmp)
	for(int i=0; i<N; i++) {
		init[0] = 0.0;			// t_0
		init[1] = 10.;			// r_0
		init[2] = 0.0;			// phi_0
		// init[3] later
		init[4] = 0.0;			// dr_0
		init[5] = 0.0;			// dphi_0
		// Set dt0
		dt0 = get_dt0(a_list[i], init[1], init[4], init[5]);
		init[3] = dt0;			// dt0
		
		tmp.set_init_value(sizeof(init)/sizeof(double), init);

		std::cout << "Start with " << i << std::endl;
		cur = a_list[i];
		tmp.setF(&F<cur>);
		std::string fileName("");
		fileName = "dat_a_";
		append(fileName, a_list[i]);
		tmp.setFileName(fileName);
		tmp.solve();
		
		std::cout << "Finished " << i << std::endl;
	}

}

template<class T> void append(std::string &stringvar, T val) {
	std::ostringstream st;
	st << val;
	stringvar.append(st.str());
}





