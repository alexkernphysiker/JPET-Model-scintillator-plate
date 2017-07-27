// this file is distributed under
// MIT license
#include <iostream>
#include <sstream>
#include <gnuplot_wrap.h>
#include <RectScin/signal_processing.h>
#include <RectScin/signal_statistics.h>
#include "model_objects/plastic_scin.h"
#include "model_objects/silicon.h"
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
		    for(double z=-2;z<=4;z+=4){
			for(double y=-6;y<=8;y+=4){
			    auto phm=hamamatsu({y,z},1.0);
			    scintillator.Surface(0,side)>>phm;
			    allside<<phm->Time();
			}
		    }
		    if(side==RectDimensions::Left){
			time_diff<<allside;
		    }else{
			auto inv=SignalInvert();
			allside>>inv;
			time_diff<<inv;
		    }
		}
		time_diff>>time_diff_stat;
		cout<<"N="<<N<<endl;
		for(size_t cnt=0;cnt<ev_n;cnt++){
			scintillator.RegisterGamma({0,0,0},N,engine);
			cout<<cnt<<" enevts         \r";
		}
		sigma_func<<point<double>(N,time_diff_stat->data().uncertainty());
		cout<<endl;
	}
	Plotter::Instance().SetOutput(".","crosscheck");
	Plot<double>().Points(sigma_func);
}
