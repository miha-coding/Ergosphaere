#include "solver.h"


Solver::Solver() {
	// Define this values here and read it from a configuration file in a later version.
	dim = 6;
	tStart = 0;
	tEnd = 800;
	N = 10000;
	fName = "./out.dat";
	y0 = vector<double>(dim);
}

Solver::Solver(const unsigned int dim, const double init[]) : Solver() {
	set_init_value(dim, init);
}

void Solver::write2file(std::ofstream &file, const double t, const vector<double>& y) {
	file << t << ",";
	for(int j=0; j<dim; j++) {
		file << y[j] << ",";
	}
	file << std::endl;
	return;
}

void Solver::set_init_value(const int dim, const double init[]) {
	this->dim = dim;
	y0 = vector<double>(dim);
	for(int i=0; i<dim; i++) {
		y0(i) = init[i];
	}
}

void Solver::solve() {
	// Runge-Kutta method (fourth-order method)
	
	// Open file to save the results.
	std::ofstream file(fName);
	if(!file.is_open()) {
		std::cerr << "Fehler beim Öffnen der Datei" << std::endl;
		return;
	}
	double h = (tEnd-tStart)/N;  // calculate step width
	double t = tStart;  // time variable
	
	vector<double> y(dim);
	y = y0;  // set initial value
	write2file(file, t, y);  // write initial values to file

	vector<double> k1(dim), k2(dim), k3(dim), k4(dim);
	for(int i=0; i<N; i++) {
		f(t, y, k1);
		f(t+h/2, y + k1*h/2, k2);
		f(t+h/2, y + k2*h/2, k3);
		f(t+h, y+h*k3, k4);
		
		y = y + h/6 * (k1 + 2*k2 + 2*k3 + k4);
		t += h;
		
		write2file(file, t, y);  // write new data to file
	}
	file.close();
}			

void Solver::print() const {
	std::cout << "dim " << dim << std::endl;
	std::cout << "t0 " << tStart << std::endl;
	std::cout << "tend " << tEnd << std::endl;
	std::cout << "N " << N << std::endl;
	std::cout << "fName " << fName << std::endl;
	for(int i=0; i<this->dim; i++) {
		std::cout << "i=" << i << " vector: " << y0[i] << std::endl;
	}
	
}
