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
const size_t ev_n=5000;
int main(int,char**){
	Plotter::Instance().SetOutput(".");
	Vec ScinSize={400,400,4},Step={75,75};
	printf("CREATE\n");
	BC420 scintillator({make_pair(0,ScinSize[0]),make_pair(0,ScinSize[1]),make_pair(0,ScinSize[2])});
	auto Correlation=make_shared<Signal2DCorrelation>();
	for(size_t dimension=0;dimension<2;dimension++){
		auto time_diff=SignalSum({1,-1});
		for(auto side=RectDimensions::Left;side<=RectDimensions::Right;inc(side)){
			auto phm=SiPhm({make_pair(0,ScinSize[dimension]),make_pair(0,ScinSize[2])},0);
			scintillator.Surface(dimension,side)>>phm;
			time_diff<<phm->Time();
		}
		Correlation<<time_diff;
	}
	printf("BEGIN\n");
	for(size_t cnt=0;cnt<ev_n;cnt++)
		scintillator.RegisterGamma({ScinSize[0]/4.0,ScinSize[1]/4.0,ScinSize[2]/2.0},3000);
	printf("END (%i events of %i registered)\n",Correlation->Points().size(),ev_n);
	PlotPoints<double,vector<Pair>>().WithoutErrors("Check",Correlation->Points());
}