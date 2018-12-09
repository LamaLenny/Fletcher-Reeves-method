#include "Stop_cr.h"

bool Stop_N_max::crit(Args* a)
{
	return(a->count >= a->N_max ? true : false);
}
const char* Stop_N_max::name() { return("iteration count is max"); }

bool Stop_x_dif::crit(Args* a)
{
	double x_dif = (a->x_cur + a->x_next.multiply_const(-1)).sq_norm();
	return(x_dif < a->eps*a->eps ? true : false);
}
const char* Stop_x_dif::name() { return("x_different less then eps"); }

bool Stop_grad_norm::crit(Args* a)
{
	double norm_2 = a->f.grad(a->x_cur, a->left, a->right, a->eps).sq_norm();
	return(norm_2 < a->eps*a->eps ? true : false);
}
const char* Stop_grad_norm::name() { return("f norm is less then eps"); }

bool Stop_good_comp::crit(Args* a)
{
	return(a->count_good >= a->N_good_max ? true : false);
}
const char* Stop_good_comp::name() { return("good iteration count is max"); }

bool Stop_some::crit()
{
	for (int i = 0; i < ps.size(); ++i)
	{
		if (ps[i]->crit(a))
		{
			*reason = ps[i]->name();
			return true;
		}
	}
	return false;
}