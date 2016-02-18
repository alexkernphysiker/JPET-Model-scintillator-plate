// this file is distributed under
// MIT license
#include <iostream>
#include <sstream>
#include <gnuplot_wrap.h>
#include <RectScin/signal_processing.h>
#include <RectScin/signal_statistics.h>
#include <plastic_scin.h>
#include <silicon.h>
using namespace std;
using namespace MathTemplates;
using namespace GnuplotWrap;
using namespace RectangularScintillator;
using namespace Model;
const size_t ev_n=10000;
int main(int,char**){
	RANDOM engine;
	LinearInterpolation<double> sigma_func;
	for(size_t N=2000;N<7000;N+=100){
		BC420 scintillator({make_pair(-150,150),make_pair(-9.5,9.5),make_pair(-3.5,3.5)});
		auto time_diff_stat=make_shared<SignalStatictics>();
		auto time_diff=make_shared<SignalSumm>();
		for(auto side=RectDimensions::Left;side<=RectDimensions::Right;inc(side)){
			auto allside=make_shared<SignalSortAndSelect>(2);
			for(double z=-Hamamatsu_width/2.0;z<=Hamamatsu_width;z+=Hamamatsu_width)
				for(double y=-Hamamatsu_width*1.5;y<=Hamamatsu_width*2;y+=Hamamatsu_width){
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
		printf("N=%i\n",N);
		for(size_t cnt=0;cnt<ev_n;cnt++){
			scintillator.RegisterGamma({0,0,0},N,engine);
			printf("%i enevts         \r",cnt);
		}
		sigma_func<<make_pair(N,time_diff_stat->data().get().delta());
		printf("\n");
	}
	Plotter::Instance().SetOutput(".","crosscheck");
	Plot<double>().Points(sigma_func);
}