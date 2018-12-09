#pragma once
#include <vector>
#include <algorithm>

using namespace std;
//!Double vector with arithmetic operations.
/*!
* This class is double vector with with addition and multiplication by a constant.
*/
class vec {
public:
	/*!
	*Double vector
	*/
	vector<double> cord;
	/*!
	*Size of vector
	*/
	size_t size() const;
	/*!
	*Constructor. Creates an empty vector.
	*/
	vec() : cord(0) {};
	/*!
	*Constructor. Creates a vector of size 'size'.
	*/
	vec(int size) : cord(size) {};
	/*!
	*Constructor. Creates a vector equal to x.
	*/
	vec(const vec& x) : cord(x.cord) {};
	/*!
	*Constructor. Creates a vector equal to x.
	*/
	vec(vector<double>& x) : cord(x) {};
	/*!
	*Operator overload =
	*/
	vec& operator=(const vec& x);
	/*!
	*Operator overload =
	*/
	vec& operator=(vec&&x);
	/*!
	*Sum of two vecors
	*/
	vec operator+(const vec&x) const;
	/*!
	*Access to the vector element for reading
	*/
	double operator[](int i) const;
	/*!
	Multiplies a vector by a constant
	*/
	vec multiply_const(double a) const;
	/*!
	Counts the square of the norm
	*/
	double sq_norm() const;
	/*!
	Prints a vector to the console.
	*/
	void print() const;

};


