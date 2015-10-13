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
int main(int,char**){
	RANDOM engine;
	BC420 scintillator({make_pair(0,ScinSize[0]),make_pair(0,ScinSize[1]),make_pair(0,ScinSize[2])});
	auto output=make_shared<SignalsToFile>();
	auto output_triggerless=make_shared<SignalsToFile>();
	{
		auto trigger=make_shared<AllSignalsPresent>();
		for(size_t dimension=0;dimension<2;dimension++){
			for(auto side=RectDimensions::Left;side<=RectDimensions::Right;inc(side)){
				auto allside=make_shared<SignalSortAndSelect2>(2);
				for(double x=PhmStep_edge[dimension]/2.0;x<ScinSize[dimension];x+=PhmStep_edge[dimension])
					for(double z=PhmStep_edge[2]/2.0;z<ScinSize[2];z+=PhmStep_edge[2]){
						auto phm=hamamatsu({x,z},1.0);
						scintillator.Surface(dimension,side)>>phm;
						allside<<phm->Time();
					}
				auto index=make_shared<Signal>(),time=make_shared<Signal>(),
					index_triggered=make_shared<Signal>(),time_triggered=make_shared<Signal>();
				allside>>index>>time;
				(trigger<<index<<time)>>index_triggered>>time_triggered;
				output<<index_triggered<<time_triggered;
				output_triggerless<<index<<time;
			}
		}
	}
	scintillator.Configure(BC420::Reflections(7));
	uniform_real_distribution<double> distrz(0,ScinSize[2]);
	for(double x=PosStep[0];x<ScinSize[0];x+=PosStep[0])
		for(double y=PosStep[1];y<ScinSize[1];y+=PosStep[1]){
			ostringstream name,name2;
			name<<"DATA."<<x<<"."<<y<<".edges.txt";
			name2<<"DATA."<<x<<"."<<y<<".edges.triggerless.txt";
			output->Redirect(name.str());
			output_triggerless->Redirect(name2.str());
			printf("BEGIN %s\n",name.str().c_str());
			for(size_t cnt=0;cnt<ev_n;cnt++)
				scintillator.RegisterGamma({x,y,distrz(engine)},3000,engine);
			printf("END %s\n",name.str().c_str());
		}
	printf("GOODBYE!\n");
}
