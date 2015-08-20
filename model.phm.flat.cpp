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
	{
		auto sort=make_shared<SignalSort2>();
		for(double x=PhmStep_flat[0]/2.0;x<ScinSize[0];x+=PhmStep_flat[0])
				for(double y=PhmStep_flat[1]/2.0;y<ScinSize[1];y+=PhmStep_flat[1]){
					auto phm=hamamatsu({x,y},1.0);
					scintillator.Surface(2,RectDimensions::Left)>>phm;
					sort<<phm->Time();
				}
		for(size_t i=0;i<8;i++){
			auto signal=make_shared<Signal>();
			sort>>signal;
			output<<signal;
		}
	}
	uniform_real_distribution<double> distrz(0,ScinSize[2]);
	for(double x=PosStep[0];x<ScinSize[0];x+=PosStep[0])
		for(double y=PosStep[1];y<ScinSize[1];y+=PosStep[1]){
			ostringstream name,name2;
			name<<"DATA."<<x<<"."<<y<<".flat.txt";
			output->Redirect(name.str());
			printf("BEGIN %s\n",name.str().c_str());
			for(size_t cnt=0;cnt<ev_n;cnt++)
				scintillator.RegisterGamma({x,y,distrz(engine)},3000,engine);
			printf("END %s\n",name.str().c_str());
		}
		printf("GOODBYE!\n");
}