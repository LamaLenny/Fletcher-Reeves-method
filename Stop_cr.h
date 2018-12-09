#pragma once
#include "FUN_vec.h"
#include <string>
#include <vector>
//!Argument class to stop.
class Args {

public:
	/*!
	*Current number of iterations.
	*/
	int count;
	/*!
	*Maximum number of iterations.
	*/
	int N_max;
	/*!
	*Argument for random search. It is a maximum number of "good" comparisons in a row (with decreasing objective function)
	*/
	int N_good_max;
	/*!
	*Argument for random search. It is a number of "good" comparisons in a row (with decreasing objective function)
	*/
	int count_good;
	/*!
	*Current approximation.
	*/
	vec x_cur;
	/*!
	*Next approximation.
	*/
	vec x_next;
	/*!
	*Epsilon.
	*/
	double eps;
	/*!
	*Objective function
	*/
	fun f;
	/*!
	*Box left border vector.
	*/
	vec left;
	/*!
	*Box right border vector.
	*/
	vec right;
	/*!
	*Constructor.
	*/
	Args(int c = 0, int N = 1000) : f(nullptr), count(c), N_max(N) {};
};

//!Virtual parent class stop criteria
class Stop {
public:
	/*!
	*Is it time to stop the iteration.
	*\return true->stop, false->not stop.
	*/
	virtual bool crit(Args* a) = 0;
	/*!
	*Criterion name
	*/
	virtual const char* name() = 0;
};

//!iteration count is max
/*!
*count >= N_max -> stop
*/
class Stop_N_max : public Stop {
public:
	bool crit(Args* a) override;	
	const char* name() override;
};

//!x_different less then eps
/*!
*||x_cur - x_next|| < eps -> stop
*/
class Stop_x_dif : public Stop {
public:
	bool crit(Args* a) override;	
	const char* name() override;
};

//!f norm is less then eps
/*!
*||f(x_cur)||<eps -> stop (for Fletcher Reeves)
*/
class Stop_grad_norm : public Stop {
public:
	bool crit(Args* a) override;
	const char* name() override;
};

//!good iteration count is max
/*!
*count_good >= N_max_good -> stop (for random search)
*/
class Stop_good_comp : public Stop {
public:
	bool crit(Args* a) override;
	const char* name() override;

};

//!The class containing the vector of pointers to criteria

class Stop_some {
public:
	/*!
	*Pointer to arguments for stopping criteria
	*/
	Args* a;
	/*!
	*Vector of pointers to criteria
	*/
	vector<Stop*> ps;
	/*!
	*The name of the criterion that caused the stop.
	*/
	string* reason;
	/*!
	*Constructor. Allocates memory for a and reason. Copies a vector of pointers to criteria.
	*/
	Stop_some()
	{
		a = new Args;
		reason = new string;
	};
	/*!
	*Constructor. Allocates memory for a and reason. 
	*/
	Stop_some(vector<Stop*>& pq) : ps(pq)
	{
		a = new Args;
		reason = new string;
	}
	/*!
	*Destructor. Delete reason and a.
	*/
	~Stop_some()
	{
		delete reason;
		delete a;	
	}
	/*!
	*Is it time to stop the iteration on any of the criteria.
	*/
	bool crit();
};