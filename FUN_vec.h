#pragma once
#include "my_vector.h"
//!Multidimensional function.
/*!
* This class is vector dependent function.
*/

class fun {
public:
	double(*pf)(vec);
	/*!
	*Constructor.
	*/
	fun(double(*pg)(vec)) : pf(pg) {};
	/*!
	*Copy constructor.
	*/
	fun(const fun& g) : pf(g.pf) {};
	/*!
	*Counts the gradient.
	*\param x0 The point at which the gradient is calculated
	*\param left, right Box borders
	*\param eps epsilon
	*\return gradient vector
	*/
	vec grad(const vec& x0, const vec& left, const vec& right, double eps) const;

};
