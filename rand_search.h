#pragma once
#include "my_vector.h"
#include "com_rand.h"
#include "FUN_vec.h"
#include "Stop_cr.h"

//!The class search for a minimum by random search.
class rs {
public:
	/*!
	*Objective function
	*/
	fun f;
	/*!
	*Initial approximation
	*/
	vec x0;
	/*!
	*Box left border vector.
	*/
	vec l;
	/*!
	*Box right border vector.
	*/
	vec r;
	/*!
	*Maximum count of iterations
	*/
	int N_max;
	/*!
	*Maximum number of "good" comparisons in a row (with decreasing objective function)
	*/
	int N_good_max;	
	/*!
	*epsilon
	*/
	double eps;
	/*!
	*The probability that a point from a uniform distribution in a neighborhood.
	*/
	double p;
	/*!
	*Stopping criteria
	*/
	Stop_some s;
	/*!
	*Constructor
	*/
	rs(double(*pg)(vec), const vec& left, const vec& right, const vec& x_0, vector<Stop*>& q, double p0 = 0.7, int N1 = 10000, int N2 = 100, double ep = 1e-9) : f(pg), l(left), r(right), x0(x_0), p(p0), N_max(N1), N_good_max(N2), eps(ep), s(q) {};
	/*!
	*Search minimum
	*/
	vec search();
};

