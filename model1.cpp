// this file is distributed under
// GPL v 3.0 license
#include <iostream>
#include <math_h/gnuplot/gnuplot.h>
#include "plastic_scin.h"
#include "silicon.h"
using namespace std;
int main(int,char**){
	Plotter::Instance().SetOutput(".");
	Vec ScinSize={300,300,4};
	double step=4;
	printf("CREATE\n");
	BC420 scintillator({make_pair(0,ScinSize[0]),make_pair(0,ScinSize[1]),make_pair(-ScinSize[2]/2.0,ScinSize[2]/2.0)});
	typedef shared_ptr<SiliconPhm> PHM;vector<PHM> matrix[2][2];
	for(unsigned int dimension=0;dimension<2;dimension++)
		for(auto side=RectDimensions::Left;side<=RectDimensions::Right;side=static_cast<decltype(side)>(side+1))
			for(double x=step/2.0;x<ScinSize[dimension];x+=step){
				auto phm=Hamamatsu_12572_100P({x,0},1);
				matrix[dimension][side].push_back(phm);
				scintillator.Surface(dimension,side)<<phm;
			}
	printf("BEGIN\n");
	for(unsigned int cnt=0;cnt<5000;cnt++){
		scintillator.RegisterGamma({ScinSize[0]/2.0,ScinSize[1]/2.0,0},3000);
		printf("N=%i\r",cnt+1);
	}
	printf("FILL\n");
	typedef LinearInterpolation<double> Tbl;
	typedef PlotPoints<double,Tbl> PlotTbl;
	vector<string> ax_n={"X-","Y-"},side_n={"left","right"};
	Tbl cntplots[2][2],cnterrors[2][2],timeplots[2][2],timeerrors[2][2],events[2][2];
	for(unsigned int dimension=0;dimension<2;dimension++)
		for(auto side=RectDimensions::Left;side<=RectDimensions::Right;inc(side))
			for(PHM phm:matrix[dimension][side]){
				events[dimension][side]<<make_pair(phm->pos()[0],phm->timer().events_count());
				cntplots[dimension][side]<<make_pair(phm->pos()[0],phm->counter().average());
				cnterrors[dimension][side]<<make_pair(phm->pos()[0],phm->counter().sigma());
				if(phm->timer().events_count()>=2){
					timeplots[dimension][side]<<make_pair(phm->pos()[0],phm->timer().average());
					timeerrors[dimension][side]<<make_pair(phm->pos()[0],phm->timer().sigma());
				}
			}
	printf("PLOT\n");
	PlotTbl Counts,Times,Events;
	for(unsigned int dimension=0;dimension<2;dimension++)
		for(auto side=RectDimensions::Left;side<=RectDimensions::Right;side=static_cast<decltype(side)>(side+1)){
			Counts.WithErrorOnX(ax_n[dimension]+side_n[side]+"-count",static_cast<Tbl&&>(cntplots[dimension][side]),cnterrors[dimension][side].func());
			Times.WithErrorOnX(ax_n[dimension]+side_n[side]+"-time",static_cast<Tbl&&>(timeplots[dimension][side]),timeerrors[dimension][side].func());
			Events.WithoutErrors(ax_n[dimension]+side_n[side]+"-events",static_cast<Tbl&&>(events[dimension][side]));
		}
	printf("END\n");
}