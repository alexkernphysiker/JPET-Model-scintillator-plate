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
		auto first=make_shared<SignalSortAndSelect2>(0),
			second=make_shared<SignalSortAndSelect2>(1),
			third=make_shared<SignalSortAndSelect2>(2);
		for(double x=PhmStep_flat[0]/2.0;x<ScinSize[0];x+=PhmStep_flat[0])
				for(double y=PhmStep_flat[1]/2.0;y<ScinSize[1];y+=PhmStep_flat[1]){
					auto phm=hamamatsu({x,y},1.0);
					scintillator.Surface(2,RectDimensions::Left)>>phm;
					first<<phm->Time();
					second<<phm->Time();
					third<<phm->Time();
				}
		auto index1=make_shared<Signal>(),time1=make_shared<Signal>(),
			index2=make_shared<Signal>(),time2=make_shared<Signal>(),
			index3=make_shared<Signal>(),time3=make_shared<Signal>();
		first>>index1>>time1;
		output<<index1<<time1;
		second>>index2>>time2;
		output<<index2<<time2;
		third>>index3>>time3;
		output<<index3<<time3;
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