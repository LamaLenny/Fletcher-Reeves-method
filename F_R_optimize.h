#pragma once
#include "FUN_vec.h"
#include "Stop_cr.h"

//!Class for finding the minimum of a function by direction

class oned_fun : public fun {
public:
	vec x;
	vec p;

	/*!
	*Constructor.
	*/
	oned_fun(double(*pg)(vec), vec& x1, vec& p1) : fun(pg), x(x1), p(p1) {};
	/*!
	*Copy constructor.
	*/
	oned_fun(const fun& g, vec& x1, vec& p1) : fun(g), x(x1), p(p1) {};
	/*!
	*Operator overload ().
	*\return f(x + a*p)
	*/
	double operator()(double a)
	{
		return pf(x + p.multiply_const(a));
	}
	/*!
	*.
	*\return min_(left <= a <= right) f(x + a*p)
	*/
	double lin_search(double left, double right, double eps = 1e-7);
};


//!The class search for a minimum by the Fletcher Reeves method.
class F_R {
public:
	/*!
	*Objective function
	*/
	fun f;
	/*!
	*Box left border vector.
	*/
	vec l;
	/*!
	*Box right border vector.
	*/
	vec r;
	/*!
	*Initial approximation
	*/
	vec x0;
	/*!
	*Maximum count of iterations
	*/
	int N_max;
	/*!
	*epsilon
	*/
	double eps;	
	/*!
	*Stopping criteria
	*/
	Stop_some s;
	/*!
	*Constructor
	*/
	F_R(double(*pg)(vec), const vec& left, const vec& right, const vec& x_0, vector<Stop*>& q, int N = 1000, double ep = 1e-9) : f(pg), l(left), r(right), x0(x_0), eps(ep), N_max(N), s(q) {};
	/*!
	*Box and Ray Crossing
	*return l and r: l<=a<=r  <=> a >= 0 and x + a*p in the box.
	*/
	pair<double, double> intersect(const vec& x, const vec& p) const;
	/*!
	*Search minimum
	*/
	vec F_R_optimize();	

};