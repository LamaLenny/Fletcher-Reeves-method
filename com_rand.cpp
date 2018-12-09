#include "com_rand.h"

std::mt19937& Generator::get_mt(){ return Generator::mt; }

double get_01()
{ 
	std::uniform_real_distribution<double> unif_real(0.0, 1.0);
	return unif_real(Generator::get_mt());
}

