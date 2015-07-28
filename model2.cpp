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
	Plotter::Instance().SetOutput(".");
	LinearInterpolation<double> time_res_center,time_res_corner;
	mutex M;
	auto proc=[&time_res_center,&time_res_corner,&M](size_t orderstatistics){
		printf("CREATE virtual setup for simulating order statistics %i\n",orderstatistics+1);
		BC420 scintillator({make_pair(0,ScinSize[0]),make_pair(0,ScinSize[1]),make_pair(0,ScinSize[2])});
		auto Correlation=make_shared<Signal2DCorrelation>();
		auto statistic_x=make_shared<SignalStatictics>();
		for(size_t dimension=0;dimension<2;dimension++){
			auto time_diff=make_shared<SignalSumm>();
			for(auto side=RectDimensions::Left;side<=RectDimensions::Right;inc(side)){
				auto allside=make_shared<SignalSortAndSelect>(orderstatistics);
				for(double x=PhmStep[dimension]/2.0;x<ScinSize[dimension];x+=PhmStep[dimension])
					for(double z=PhmStep[2]/2.0;z<ScinSize[2];z+=PhmStep[2]){
						auto phm=hamamatsu({x,z},1.0);
						scintillator.Surface(dimension,side)>>phm;
						allside<<phm->Time();
					}
					auto exit=make_shared<Signal>();
				if(side==RectDimensions::Left)
					allside>>exit;
				else
					allside>>(SignalInvert()>>exit);
				time_diff<<exit;
			}
			Correlation<<time_diff;
			if(dimension==0)
				time_diff>>statistic_x;
		}
		for(double x=PosStep[0];x<ScinSize[0];x+=PosStep[0])
			for(double y=PosStep[1];y<ScinSize[1];y+=PosStep[1]){
				default_random_engine rnd;
				uniform_real_distribution<double> distr(0,ScinSize[2]);
				ostringstream name;
				name<<"Pos("<<x<<","<<y<<")["<<orderstatistics+1<<"]";
				
				printf("BEGIN %s\n",name.str().c_str());
				for(size_t cnt=0;cnt<ev_n;cnt++)
					scintillator.RegisterGamma({x,y,distr(rnd)},3000);
				printf("END (%i events of %i registered)\n",Correlation->Points().size(),ev_n);
				{
					lock_guard<mutex> lock(M);
					PlotPoints<double,vector<Pair>>().WithoutErrors(name.str(),Correlation->Points());
					if((pow(x-(ScinSize[0]/2.0),2)<1.0)&&(pow(y-(ScinSize[1]/2.0),2)<1.0))
						time_res_center<<make_pair(orderstatistics,statistic_x->data().getSigma());
					if((pow(x-(PosStep[0]),2)<1.0)&&(pow(y-(PosStep[1]),2)<1.0))
						time_res_corner<<make_pair(orderstatistics,statistic_x->data().getSigma());
				}
				Correlation->Clear();
				statistic_x->Clear();
			}
	};
	{
		vector<shared_ptr<thread>> THR;
		for(size_t orderstatistics=0;orderstatistics<10;orderstatistics++)
			THR.push_back(make_shared<thread>(proc,orderstatistics));
		for(auto thr:THR)thr->join();
	}
	PlotPoints<double,decltype(time_res_center)>()
		.WithoutErrors("Sigma_t center",static_right(time_res_center))
		.WithoutErrors("Sigma_t corner",static_right(time_res_corner));
}