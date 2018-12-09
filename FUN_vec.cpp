#include "FUN_vec.h"

vec fun::grad(const vec& x0, const vec& left, const vec& right, double eps) const
{
	vec x(x0);
	vec y(x0);
	vec res(x.size());

	double h1 = eps;
	double h2 = eps;
	for (int i = 0; i < x.size(); ++i)
	{

		h1 = eps;
		h2 = eps;
		if (x[i] + eps > right[i])
			h1 = (right[i] - x[i]) / 2;
		if (x[i] - eps < left[i])
			h2 = (x[i] - left[i]) / 2;

		x.cord[i] += h1;
		y.cord[i] -= h2;
		res.cord[i] = ((*pf)(x) - (*pf)(y)) / (h1 + h2);
		x.cord[i] -= h1;
		double a = h1 + h2;
		y.cord[i] += h2;
	}
	return res;
}