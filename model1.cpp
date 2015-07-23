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
int main(int,char**){
	Plotter::Instance().SetOutput(".");
	Vec ScinSize={300,300,4},Step={75,75};
	printf("CREATE\n");
	BC420 scintillator({make_pair(0,ScinSize[0]),make_pair(0,ScinSize[1]),make_pair(0,ScinSize[2])});
	auto Correlation=make_shared<Signal2DCorrelation>();
	for(size_t dimension=0;dimension<2;dimension++){
		auto time_diff=SignalSum({1,-1});
		for(auto side=RectDimensions::Left;side<=RectDimensions::Right;inc(side)){
			double length=ScinSize[dimension];
			auto phm=SiPhm({make_pair(0,ScinSize[dimension]),make_pair(0,ScinSize[2])},0);
			scintillator.Surface(dimension,side)>>phm;
			time_diff<<phm->Time();
		}
		Correlation<<time_diff;
	}
	PlotPoints<double,vector<Pair>> plot;
	for(double x=Step[0];x<ScinSize[0];x+=Step[0])for(double y=Step[1];y<ScinSize[1];y+=Step[1]){
		default_random_engine rnd;
		uniform_real_distribution<double> distr(0,ScinSize[2]);
		ostringstream name;
		name<<"Pos("<<x<<","<<y<<")";
		printf("BEGIN %s\n",name.str().c_str());
		const size_t ev_n=500;
		for(size_t cnt=0;cnt<ev_n;cnt++)
			scintillator.RegisterGamma({x,y,distr(rnd)},3000);
		printf("END (%i events of %i registered)\n",Correlation->Points().size(),ev_n);
		plot.WithoutErrors(name.str(),Correlation->Points());
		Correlation->Clear();
	}
}