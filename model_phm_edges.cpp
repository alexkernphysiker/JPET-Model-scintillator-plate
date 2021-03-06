// this file is distributed under
// MIT license
#include <iostream>
#include <sstream>
#include <gnuplot_wrap.h>
#include <math_h/tabledata.h>
#include <RectScin/signal_processing.h>
#include <RectScin/signal_statistics.h>
#include "model_objects/plastic_scin.h"
#include "model_objects/silicon.h"
using namespace std;
using namespace MathTemplates;
using namespace GnuplotWrap;
using namespace RectangularScintillator;
using namespace Model;
const size_t ev_n=200;
Vec ScinSize={1000,1000,80},PosStep={ScinSize[0]/8.0,ScinSize[1]/8.0},
PhmStep_edge={4,4,4};
int main(int,char**){
	Plotter::Instance().SetOutput(".","model.phm.edges.plot");
	for(size_t order_statistic=0;order_statistic<3;order_statistic++){
		Distribution2D<double> place_reconstruction(BinsByStep(-10.0,0.25,+10.0),BinsByStep(-10.0,0.25,+10.0));
		BC420 scintillator({make_pair(0,ScinSize[0]),make_pair(0,ScinSize[1]),make_pair(0,ScinSize[2])});
		auto output=make_shared<SignalsToFile>();
		{
			auto hist_fill=make_shared<SignalsAnalyse>([&place_reconstruction](const Vec&P){
				place_reconstruction.Fill(P[0],P[1]);
			});
			auto trigger=make_shared<AllSignalsPresent>();
			for(size_t dimension=0;dimension<2;dimension++){
				auto time_diff=make_shared<SignalSumm>();
				for(auto side=RectDimensions::Left;side<=RectDimensions::Right;inc(side)){
					auto allside=make_shared<SignalSortAndSelect2>(order_statistic);
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
					auto pin2diff=SignalMultiply(pow(-1.0,double(int(side))));
					time_triggered>>pin2diff;
					time_diff<<pin2diff;
				}
				hist_fill<<time_diff;
			}
		}
		scintillator.Configure(BC420::Reflections(7));
		RandomUniform<> distrz(0,ScinSize[2]);
		for(double x=PosStep[0];x<ScinSize[0];x+=PosStep[0])
			for(double y=PosStep[1];y<ScinSize[1];y+=PosStep[1]){
				ostringstream name,name2;
				name<<"DATA."<<x<<"."<<y<<".edges."<<order_statistic<<".txt";
				output->Redirect(name.str());
				cout<<"BEGIN "<<name.str()<<endl;
				for(size_t cnt=0;cnt<ev_n;cnt++)
					scintillator.RegisterGamma({x,y,distrz()},3000);
				cout<<"END "<<name.str()<<endl;
			}
		PlotHist2d(sp2).Distr(place_reconstruction,to_string(order_statistic));
		PlotHist2d(normal).Distr(place_reconstruction,to_string(order_statistic));
	}
	cout<<"GOODBYE!"<<endl;
}
