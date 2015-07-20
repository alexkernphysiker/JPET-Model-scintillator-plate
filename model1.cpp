// this file is distributed under
// GPL v 3.0 license
#include <iostream>
#include <math_h/gnuplot/gnuplot.h>
#include "plastic_scin.h"
#include "silicon.h"
using namespace std;
int main(int,char**){
	Plotter::Instance().SetOutput(".");
	double length=100;
	double width=10;
	double height=5;
	double step=5;
	
	BC420 scintillator({make_pair(0,length),make_pair(0,width),make_pair(0,height)});
	
	typedef shared_ptr<SiliconPhm> PHM;vector<PHM> matrix;
	for(double x=step/2.0;x<length;x+=step)matrix.push_back(TestPhm({x,width/2.0},step));
	for(PHM phm:matrix)scintillator.Surface(2,RectDimensions::Left)<<phm;
	
	for(unsigned int cnt=0;cnt<100;cnt++)scintillator.RegisterGamma({length/2.0,width/2.0,height/2.0},3000);
	
	typedef LinearInterpolation<double> Tbl;
	typedef PlotPoints<double,Tbl> PlotTbl;
	Tbl count,counterror,time,timeerror;
	for(PHM phm:matrix){
		double x=phm->pos()[0];
		count<<make_pair(x,phm->counter().average());
		counterror<<make_pair(x,phm->counter().sigma());
		time<<make_pair(x,phm->timer().average());
		timeerror<<make_pair(x,phm->timer().sigma());
	}
	PlotTbl().WithErrorOnX("Photoelectrons",static_left(count),[&counterror](double x){return counterror(x);});
	PlotTbl().WithErrorOnX("Time",static_left(time),[&timeerror](double x){return timeerror(x);});
}