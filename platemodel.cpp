// this file is distributed under
// GPL v 3.0 license
#include <iostream>
#include <math_h/gnuplot/gnuplot.h>
#include <rectscin.h>
#include <lightguide.h>
#include <sensitive.h>
#include <signal_model.h>
using namespace std;
int main(int,char**){
	auto time_distribution=TimeDistribution2(0.005,0.2,1.5);
	RandomValueGenerator<double> lambda_distribution([](double l){return 1.0;},360,480,2);
	auto efficiency=[](double l){return 0.3;};
	auto absorption=[](double l){return 0.08;};
	double refraction=1.58;
	RectangularScintillator scintillator(
		{make_pair(0,30),make_pair(0,500),make_pair(0,500)},
		time_distribution,lambda_distribution,refraction,absorption
	);
	
}