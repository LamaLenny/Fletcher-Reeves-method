#include "F_R_optimize.h"
#include <cmath>
#include <iostream> 
//#include <boost/math/tools/minima.hpp>
#include "brent.hpp"
#include <algorithm>

using namespace std;
double oned_fun::lin_search(double left, double right, double eps)
{
	double h = (right - left) / 10;
	double m_f = (*this)(left);
	double m_x = left;
	for (int i = 0; i < 10; ++i)
	{
		//pair<double, double> z = boost::math::tools::brent_find_minima(*this, left, left + h, 20);
		double z = brent::local_min(*this, left, left + h, eps);
		double f_z = (*this)(z);
		if ( f_z < m_f)
		{
			m_f = f_z;
			m_x = z;
		}
		left += h;
	}
	return m_x;
}
pair<double, double> F_R::intersect(const vec& x, const vec& p) const
{
	pair<double, double> result(0, INT_MAX);
	for (int i = 0; i < x.size(); ++i)
	{
		if (p[i] == 0) continue;
		double h1 = (l[i] - x[i]) / p[i];
		double h2 = (r[i] - x[i]) / p[i];
		if (p[i] < 0)
		{
			std::swap(h1, h2);
		}

		result.first = std::max(result.first, h1);
		result.second = std::min(result.second, h2);
	}
	return result;
}

vec F_R::F_R_optimize()
{
	vec x = x0;
	vec grad_cur = f.grad(x, l, r, eps);
	vec grad_next;
	vec p = grad_cur.multiply_const(-1);
	
	s.a->f = f;
	s.a->N_max = N_max;
	s.a->eps = eps;
	s.a->left = l;
	s.a->right = r;

	for(s.a->count = 0;  ; ++(s.a->count))
	{
		s.a->x_cur = x;
		pair<double, double> interval = intersect(x, p);
		oned_fun g(f, x, p);
		double a = g.lin_search(interval.first, interval.second, eps);
		x = x + p.multiply_const(a);
		s.a->x_next = x;
		grad_next = f.grad(x, l, r, eps);
		double b = grad_next.sq_norm() / grad_cur.sq_norm();
		p = grad_next.multiply_const(-1) + p.multiply_const(b);
		grad_cur = grad_next;
		if (s.crit())
		{
			break;
		}
	}
	return x;
}

