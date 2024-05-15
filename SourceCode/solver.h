#ifndef SOLVER_H
#define SOLVER_H

#include<boost/numeric/ublas/matrix.hpp>
#include<boost/numeric/ublas/vector.hpp>
#include<boost/numeric/ublas/io.hpp>
#include<iostream>
#include<fstream>
#include<string>
#include<memory>

using namespace boost::numeric::ublas;


class Solver{
private:
	int dim; // Dimension of the DGL
	double tStart;  // Start time
	double tEnd;  // End time
	int N;  // Number of steps
	vector<double> y0;  // initial value
	std::string fName; // Filename for the computed Data
	void (*f)(const double, const vector<double>&, vector<double>&);

public:
	Solver();
	Solver(const unsigned int dim, const double init[]);
	void solve();
	void write2file(std::ofstream &file, const double t, const vector<double>& y);
	void set_tStart(const double tStart) { this->tStart = tStart; }
	void set_tEnd(const double tEnd) { this->tEnd = tEnd; }
	void setFileName(const std::string fName) { this->fName = fName; }
	void setF(void (*f)(const double, const vector<double>&, vector<double>&)) { this->f=f; }
	void set_init_value(const int dim, const double init[]);
	void set_N(const int N) { this->N = N; }
	void print() const;
};



#endif
