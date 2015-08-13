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
	auto output=make_shared<SignalsToFile>(),
	output_triggerless=make_shared<SignalsToFile>();
	{
		auto trigger=make_shared<AllSignalsPresent>();
		for(size_t dimension=0;dimension<2;dimension++){
			for(auto side=RectDimensions::Left;side<=RectDimensions::Right;inc(side)){
				auto allside=make_shared<SignalSortAndSelect2>(0);size_t cnt=0;
				for(double x=PhmStep_edge[dimension]/2.0;x<ScinSize[dimension];x+=PhmStep_edge[dimension])
					for(double z=PhmStep_edge[2]/2.0;z<ScinSize[2];z+=PhmStep_edge[2]){
						auto phm=hamamatsu({x,z},1.0);
						scintillator.Surface(dimension,side)>>phm;
						allside<<phm->Time();cnt++;
					}
				printf("Dimension: %i; Side: %i; %i channels \n",dimension,side,cnt);
				auto index=make_shared<Signal>(),time=make_shared<Signal>(),
				index_triggered=make_shared<Signal>(),time_triggered=make_shared<Signal>();
				allside>>index>>time;
				(trigger<<index<<time)>>index_triggered>>time_triggered;
				output<<index_triggered<<time_triggered;
				output_triggerless<<index<<time;
			}
		}{
			auto allside=make_shared<SignalSortAndSelect2>(0);size_t cnt=0;
			for(double x=PhmStep_flat[0]/2.0;x<ScinSize[0];x+=PhmStep_flat[0])
				for(double y=PhmStep_flat[1]/2.0;y<ScinSize[1];y+=PhmStep_flat[1]){
					auto phm=hamamatsu({x,y},1.0);
					scintillator.Surface(2,RectDimensions::Left)>>phm;
					allside<<phm->Time();cnt++;
				}
				printf("flat; %i channels \n",cnt);
			auto index=make_shared<Signal>(),time=make_shared<Signal>(),
			index_triggered=make_shared<Signal>(),time_triggered=make_shared<Signal>();
			allside>>index>>time;
			(trigger<<index<<time)>>index_triggered>>time_triggered;
			output<<index_triggered<<time_triggered;
			output_triggerless<<index<<time;
		}
	}
	uniform_real_distribution<double> distrz(0,ScinSize[2]);
	for(double x=PosStep[0];x<ScinSize[0];x+=PosStep[0])
		for(double y=PosStep[1];y<ScinSize[1];y+=PosStep[1]){
			ostringstream name,name2;
			name<<"DATA."<<x<<"."<<y<<".edges_plus_flat.txt";
			name2<<"DATA."<<x<<"."<<y<<".edges_plus_flat.triggerless.txt";
			output->Redirect(name.str());
			output_triggerless->Redirect(name2.str());
			printf("BEGIN %s\n",name.str().c_str());
			for(size_t cnt=0;cnt<ev_n;cnt++)
				scintillator.RegisterGamma({x,y,distrz(engine)},3000,engine);
			printf("END %s\n",name.str().c_str());
		}
		printf("GOODBYE!\n");
}