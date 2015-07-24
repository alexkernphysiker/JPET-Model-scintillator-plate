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
const size_t ev_n=1000;
int main(int,char**){
	Plotter::Instance().SetOutput(".");
	Vec ScinSize={Hamamatsu::Width()*100,Hamamatsu::Width()*100,Hamamatsu::Width()},
		Step={Hamamatsu::Width()*25,Hamamatsu::Width()*25};
	vector<Pair> time_res_x,artefacts;
	for(size_t orderstatistics=0;orderstatistics<20;orderstatistics++){
		printf("CREATE virtual setup for simulating order statistics %i\n",orderstatistics+1);
		BC420 scintillator({make_pair(0,ScinSize[0]),make_pair(0,ScinSize[1]),make_pair(0,ScinSize[2])});
		auto Correlation=make_shared<Signal2DCorrelation>();
		auto statistic_x=make_shared<SignalStatictics>();
		for(size_t dimension=0;dimension<2;dimension++){
			auto time_diff=SignalSum({1,-1});
			for(auto side=RectDimensions::Left;side<=RectDimensions::Right;inc(side)){
				auto allside=make_shared<SignalSortAndSelect>(orderstatistics);
				for(double step=Hamamatsu::Width(),x=step/2.0;x<ScinSize[dimension];x+=step){
					auto phm=hamamatsu({x,step/2.0},1.0);
					scintillator.Surface(dimension,side)>>phm;
					allside<<phm->Time();
				}
				time_diff<<allside;
			}
			Correlation<<time_diff;
			if(dimension==0)
				time_diff>>statistic_x;
		}
		PlotPoints<double,vector<Pair>> plot;
		for(double x=Step[0];x<ScinSize[0];x+=Step[0])
			for(double y=Step[1];y<ScinSize[1];y+=Step[1]){
				default_random_engine rnd;
				uniform_real_distribution<double> distr(0,ScinSize[2]);
				ostringstream name;
				name<<"Pos("<<x<<","<<y<<")["<<orderstatistics+1<<"]";
				printf("BEGIN %s\n",name.str().c_str());
				for(size_t cnt=0;cnt<ev_n;cnt++)
					scintillator.RegisterGamma({x,y,distr(rnd)},3000);
				printf("END (%i events of %i registered)\n",Correlation->Points().size(),ev_n);
				if((pow(x-(ScinSize[0]/2.0),2)<1.0)&&(pow(y-(ScinSize[1]/2.0),2)<1.0))
					time_res_x.push_back(make_pair(orderstatistics,statistic_x->data().getSigma()));
				plot.WithoutErrors(name.str(),Correlation->Points());
				if((pow(x-(Step[0]),2)<1.0)&&(pow(y-(Step[1]),2)<1.0)){
					double art=0;
					for(auto&p:Correlation->Points())
						if((p.first>=0)&&(p.second>=0))
							art++;
					artefacts.push_back(make_pair(orderstatistics,art/double(Correlation->Points().size())));
				}
				Correlation->Clear();
				statistic_x->Clear();
			}
	}
	PlotPoints<double,vector<Pair>>().WithoutErrors("time resolution in the center",static_right(time_res_x));
	PlotPoints<double,vector<Pair>>().WithoutErrors("Artefacts amount for corner",static_right(artefacts));
}