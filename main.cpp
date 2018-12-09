#include "F_R_optimize.h"
#include "rand_search.h"
#include <cmath>
#include <iostream>
#include <vector>

std::mt19937 Generator::mt;
using namespace std;

double f1(vec x)
{
	return ((1 - x[0])*(1 - x[0]) + 100 * (x[1] - x[0] * x[0])*(x[1] - x[0] * x[0]));
}
double f2(vec x)
{
	return (x[0]*x[0] + x[1]*x[1] + x[2]*x[2]);
}
double f3(vec x)
{
	double res = x[0];
	for(int i = 0; i < 6; ++i)
	{
		res *= x[0];
	}
	return(res + 5);
}

void input_ind(int& ind)	//Enter 0 or 1
{
	double ind_d = -1.;
	while (!(ind_d == 0 || ind_d == 1))
	while (std::cout << "Please, enter 0 or 1 (0 - No, 1 - Yes)\n"&& !(std::cin >> ind_d)) {
		std::cin.clear();
		std::string line;
		std::getline(std::cin, line);
		std::cout << "\nSorry, but your input is not a number\n" << std::endl;
	}
	if (!(ind_d == 0|| ind_d == 1)) {
		std::cout << "\nSorry, but your input is not 0 or 1. Try again\n" << std::endl;
	}
	else {
		ind = (int)ind_d;
	}
}

void input_doub_01(double& epsilon)	//Enter double >0 and <1
{
	 epsilon = 0;
	while (epsilon >= 1 || epsilon <= 0) {
		if (cout << "Please, enter number >0 and <1\n" && !(cin >> epsilon))
		{
			std::cin.clear();
			std::string line;
			std::getline(std::cin, line);
			cout << "Sorry, but your input is not a number" << endl;
		}
		else if (epsilon >= 1 || epsilon <= 0) {
			cout << "Sorry, but your input is wrong. Try again" << endl;
		}
	}
}

void input_max_count(int& N)
{
	double count_d = 0, intpart;
	while (count_d <= 0 || modf(count_d, &intpart) != 0) {
		while (cout << "Please, enter a positive integer\n " && !(cin >> count_d))
		{

			std::cin.clear();
			std::string line;
			std::getline(std::cin, line);
			cout << "\nSorry, but this is not a number\n" << endl;
		}
		if (count_d <= 0 || modf(count_d, &intpart) != 0)
		{
			cout << "\nSorry, but your input is not a positive integer. Please, try again\n" << endl;
		}
		else {
			N = (int)count_d;
		}
	}
}

void input_number(double& number)
{
	number = 0;
	while (std::cout << "Please, enter a number\n"&& !(std::cin >> number)) {
		std::cin.clear();
		std::string line;
		std::getline(std::cin, line);
		std::cout << "Sorry, but your input is not a number" << endl;
	}
}
int main()
{
	std::cout << "\n************************* Optimization Program *************************\n" << std::endl;
	double(*pf)(vec) = &f1;
	int dim = 2;
	std::cout << "\nChoose your function:\n"
		<< "< 1 > (1 - x)^2 + 100 * (y - x^2)^2\n"
		<< "< 2 > x^2 + y^2 + z^2\n"
		<< "< 3 > x^8 + 5\n"
		<< std::endl;

	int number;
	double number_d = 0;

	while (!(number_d == 1 || number_d == 2 || number_d == 3)) {
		while (std::cout << "Please, enter a number (1, 2 or 3)\n "
			&& !(std::cin >> number_d)) {

			std::cin.clear();
			std::string line;
			std::getline(std::cin, line);
			std::cout << "\nSorry, but your input is not a number" << std::endl;
		}
		if (!(number_d == 1 || number_d == 2 || number_d == 3)) {
			std::cout << "\nSorry, but your input is not 1, 2 or 3. Try again" << std::endl;
		}
		else {
			number = (int)number_d;
		}
	}
	cout << endl;
	switch (number) {
	case 1: {
		pf = &f1;
		dim = 2;
		break;
	}
	case 2: {
		pf = &f2;
		dim = 3;
		break;
	}
	case 3: {
		pf = &f3;
		dim = 1;
		break;
	}
	default:
		break;
	}

	vector<double> left;
	vector<double> right;
	vector<double> x0;
	double num;
	cout << "Enter left borders" << endl;
	for (int i = 0; i < dim; ++i)
	{
		input_number(num);
		left.push_back(num);
	}
	cout << endl;
	cout << "Enter right borders" << endl;
	for (int i = 0; i < dim; ++i)
	{
		input_number(num);
		while(num <= left[i])
		{
			cout << "This number is to the left of the left border. Please, try again." << endl;
			input_number(num);
		}
		right.push_back(num);
	}
	cout << "Enter initial approximation" << endl;
	for (int i = 0; i < dim; ++i)
	{
		input_number(num);
		while (num <= left[i] or num >= right[i])
		{
			cout << "This number is not in the box. Please, try again." << endl;
			input_number(num);
		}
		x0.push_back(num);
	}
	cout << endl;
	vec l(left);
	vec r(right);
	vec x(x0); //= (r + l).multiply_const(0.5);

	std::cout << "************************* Fletcher Reeves" << std::endl;
	vector<Stop*> ps_FR(1);
	ps_FR[0] = new Stop_N_max;
	

	int N_max;
	cout << "Enter maximum count of iteration. ";
	input_max_count(N_max);
	cout << endl;

	double epsilon;
	cout << "Enter epsilon." << endl;
	input_doub_01(epsilon);
	cout << endl;

	int ind;
	cout << "Do you want to stop if ||x_(k+1) - x_(k)|| < eps?\n" << endl;
	input_ind(ind);
	cout << endl;
	if (ind)
		ps_FR.push_back(new Stop_x_dif);

	cout << "Do you want to stop if ||grad f(x_k)|| < eps?\n" << endl;
	input_ind(ind);
	cout << endl;
	if (ind)
		ps_FR.push_back(new Stop_grad_norm);
	F_R q(pf, l, r, x, ps_FR, N_max, epsilon);
	cout << "Fletcher-Reeves" << endl;
	q.F_R_optimize().print();
	cout << *(q.s.reason) << endl;
	cout << "Count of iteration: " << q.s.a->count << endl << endl;
	for (int i = 0; i < ps_FR.size(); ++i)
		delete ps_FR[i];

	std::cout << "************************* Random search" << std::endl;
	cout << "Enter maximum count of iteration. ";
	input_max_count(N_max);
	cout << endl;

	cout << "Enter epsilon." << endl;
	input_doub_01(epsilon);
	cout << endl;

	double p;
	cout << "Enter p (the probability that a point from a uniform distribution in a neighborhood)" << endl;
	input_doub_01(p);
	cout << endl;

	int N_good_max = 0;
	vector<Stop*> ps_rs(1);
	ps_rs[0] = new Stop_N_max;
	cout << "Do you want to stop if count of good iteration (with decreasing objective function) is too big?" << endl;
	input_ind(ind);
	cout << endl;
	if (ind)
	{
		cout << "Input max count of good iteration.\n"<< endl;
		input_max_count(N_good_max);
		ps_rs.push_back(new Stop_good_comp);
	}
	rs b(pf, l, r, x, ps_rs, p, N_max, N_good_max, epsilon);
	cout << "Random search" << endl;
	b.search().print();
	cout << *(b.s.reason) << endl;
	cout << "Count of iteration: " << b.s.a->count << endl;
	for (int i = 0; i < ps_rs.size(); ++i)
		delete ps_rs[i];
	
	system("pause");
	return 0;
}