#include "my_vector.h"
#include <iostream>


size_t vec::size() const
{
	return cord.size();
}

vec& vec::operator=(const vec& x)
{
	cord = x.cord;
	return *this;
}

vec& vec::operator=(vec&&x)
{
	cord = x.cord;
	return *this;
}

vec vec::operator+(const vec&x) const
{
	int s = std::min(size(), x.size());
	vec res(s);
	for (int i = 0; i < s; ++i)
		res.cord[i] = cord[i] + x.cord[i];
	return res;
}

double vec::operator[](int i) const
{
	return cord[i];
}
vec vec::multiply_const(double a) const
{
	vec res(size());
	for (int i = 0; i < size(); ++i)
		res.cord[i] = cord[i] * a;
	return res;
}

double vec::sq_norm() const
{
	double res = 0;
	for (int i = 0; i < size(); ++i)
		res += cord[i] * cord[i];
	return res;
}

void vec::print() const
{
	for (int i = 0; i < size(); ++i)
		cout << cord[i] << endl;
}