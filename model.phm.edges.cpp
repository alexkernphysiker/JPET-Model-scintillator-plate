// this file is distributed under
// GPL v 3.0 license
#include <iostream>
#include <sstream>
#include <signal_processing.h>
#include <signal_statistics.h>
#include "plastic_scin.h"
#include "silicon.h"
using namespace std;
#include "model.params.cc"
Vec PhmStep={Hamamatsu::Width(),Hamamatsu::Width(),Hamamatsu::Width()};
int main(int,char**){
	BC420 scintillator({make_pair(0,ScinSize[0]),make_pair(0,ScinSize[1]),make_pair(0,ScinSize[2])});
	auto output=make_shared<SignalsToFile>();{
		for(size_t dimension=0;dimension<2;dimension++){
			for(auto side=RectDimensions::Left;side<=RectDimensions::Right;inc(side)){
				auto allside=make_shared<SignalSortAndSelect2>(0);
				for(double x=PhmStep[dimension]/2.0;x<ScinSize[dimension];x+=PhmStep[dimension])
					for(double z=PhmStep[2]/2.0;z<ScinSize[2];z+=PhmStep[2]){
						auto phm=hamamatsu({x,z},1.0);
						scintillator.Surface(dimension,side)>>phm;
						allside<<phm->Time();
					}
				auto index=make_shared<Signal>(),time=index=make_shared<Signal>();
				allside>>index>>time;
				output<<index<<time;
			}
		}
	}
	for(double x=PosStep[0];x<ScinSize[0];x+=PosStep[0])
		for(double y=PosStep[1];y<ScinSize[1];y+=PosStep[1]){
			default_random_engine rnd;
			uniform_real_distribution<double> distr(0,ScinSize[2]);
			ostringstream name;
			name<<"DATA."<<x<<"."<<y<<".edges.txt";
			output->Redirect(name.str());
			printf("BEGIN %s\n",name.str().c_str());
			for(size_t cnt=0;cnt<ev_n;cnt++)
				scintillator.RegisterGamma({x,y,distr(rnd)},3000);
			printf("END %s\n",name.str().c_str());
		}
	printf("GOODBYE!\n");
}