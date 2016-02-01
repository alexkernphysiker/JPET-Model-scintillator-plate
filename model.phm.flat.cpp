// this file is distributed under
// MIT license
#include <iostream>
#include <sstream>
#include <RectScin/signal_processing.h>
#include <RectScin/signal_statistics.h>
#include "plastic_scin.h"
#include "silicon.h"
using namespace std;
using namespace MathTemplates;
using namespace RectangularScintillator;
using namespace Model;
const size_t ev_n=10000;
Vec ScinSize={1000,1000,80},PosStep={ScinSize[0]/8.0,ScinSize[1]/8.0},
PhmStep_edge={Hamamatsu_width,Hamamatsu_width,Hamamatsu_width},
PhmStep_flat={Hamamatsu_width,Hamamatsu_width};
int main(int,char**){
	RANDOM engine;
	BC420 scintillator({make_pair(0,ScinSize[0]),make_pair(0,ScinSize[1]),make_pair(0,ScinSize[2])});
	auto output=make_shared<SignalsToFile>();
	{
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
				output<<index<<time;
			}
		}
		{
			auto allside=make_shared<SignalSortAndSelect2>(0);
			for(double x=PhmStep_flat[0]/2.0;x<ScinSize[0];x+=PhmStep_flat[0])
				for(double y=PhmStep_flat[1]/2.0;y<ScinSize[1];y+=PhmStep_flat[1]){
					auto phm=hamamatsu_edgeless({x,y},1.0);
					scintillator.Surface(2,RectDimensions::Left)>>phm;
					allside<<phm->Time();
				}
			auto index=make_shared<Signal>(),time=make_shared<Signal>(),
			index_triggered=make_shared<Signal>(),time_triggered=make_shared<Signal>();
			allside>>index>>time;
			output<<index<<time;
		}
	}
	scintillator.Configure(BC420::Reflections(7));
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