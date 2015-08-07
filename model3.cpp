// this file is distributed under
// GPL v 3.0 license
#include <iostream>
#include <sstream>
#include <signal_processing.h>
#include <signal_statistics.h>
#include <math_h/gnuplot/gnuplot.h>
#include "plastic_scin.h"
#include "silicon.h"
using namespace std;
#include "model_params.h"
Vec PhmStep={Hamamatsu::Width(),Hamamatsu::Width(),Hamamatsu::Width()};
int main(int,char**){
	Plotter::Instance().SetOutput(".","3.");
	
}