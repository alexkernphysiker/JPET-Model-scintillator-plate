// this file is distributed under
// GPL v 3.0 license
#include <iostream>
#include <signal_processing.h>
#include <signal_statistics.h>
#include <math_h/gnuplot/gnuplot.h>
#include "plastic_scin.h"
#include "silicon.h"
using namespace std;
int main(int,char**){
	Plotter::Instance().SetOutput(".");
	Vec ScinSize={300,300,4};
	double step=4;
	printf("CREATE\n");
	BC420 scintillator({make_pair(0,ScinSize[0]),make_pair(0,ScinSize[1]),make_pair(-ScinSize[2]/2.0,ScinSize[2]/2.0)});
	printf("BEGIN\n");
	for(unsigned int cnt=0;cnt<5000;cnt++){
		scintillator.RegisterGamma({ScinSize[0]/2.0,ScinSize[1]/2.0,0},3000);
		printf("N=%i\r",cnt+1);
	}
	printf("FILL\n");
	printf("PLOT\n");
	printf("END\n");
}