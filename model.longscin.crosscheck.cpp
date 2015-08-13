// this file is distributed under
// GPL v 3.0 license
#include <iostream>
#include <sstream>
#include <math_h/gnuplot/gnuplot.h>
#include <signal_processing.h>
#include <signal_statistics.h>
#include "plastic_scin.h"
#include "silicon.h"
using namespace std;
int main(int,char**){
	RANDOM engine;
	BC420 scintillator({make_pair(-150,150),make_pair(-9.5,9.5),make_pair(-3.5,3.5)});
	auto time_diff_stat=make_shared<SignalStatictics>();
	auto time_diff=make_shared<SignalSumm>();
	for(auto side=RectDimensions::Left;side<=RectDimensions::Right;inc(side)){
		auto allside=make_shared<SignalSortAndSelect>(2);
		for(double z=-Hamamatsu::Width()/2.0;z<=Hamamatsu::Width();z+=Hamamatsu::Width())
			for(double y=-Hamamatsu::Width()*1.5;y<=Hamamatsu::Width()*2;y+=Hamamatsu::Width()){
				printf(" %f; %f \n",z,y);
				auto phm=hamamatsu({y,z},1.0);
				scintillator.Surface(0,side)>>phm;
				allside<<phm->Time();
			}
		if(side==RectDimensions::Left)
			time_diff<<allside;
		else{
			auto inv=SignalInvert();
			allside>>inv;
			time_diff<<inv;
		}
	}
	time_diff>>time_diff_stat;
	LinearInterpolation<double> sigma_func;
	for(size_t N=2000;N<7000;N+=300){
		time_diff_stat->Clear();
		scintillator.RegisterGamma({0,0,0},N,engine);
		sigma_func<<make_pair(N,time_diff_stat->data().getSigma());
	}
	Plotter::Instance().SetOutput(".","crosscheck");
	PlotPoints<double,decltype(sigma_func)>().WithoutErrors("Crosscheck",static_right(sigma_func));
}