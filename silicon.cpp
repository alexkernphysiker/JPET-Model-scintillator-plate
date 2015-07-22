#include "silicon.h"
using namespace std;
LinearInterpolation<double> Efficiency({
	make_pair(140,     0),
	make_pair(160,     0),
	make_pair(180,     0),
	make_pair(200,     33),
	make_pair(340,     43),
	make_pair(380,     45),
	make_pair(400,     49),
	make_pair(420,     54),
	make_pair(440,     58),
	make_pair(460,     64),
	make_pair(480,     68),
	make_pair(500,     72),
	make_pair(520,     73),
	make_pair(540,     76),
	make_pair(560,     79),
	make_pair(580,     82),
	make_pair(600,     82),
	make_pair(620,     83),
	make_pair(640,     84),
	make_pair(660,     84),
	make_pair(680,     83),
	make_pair(700,     82),
	make_pair(720,     80),
	make_pair(740,     78),
	make_pair(760,     75),
	make_pair(780,     73),
	make_pair(800,     69),
	make_pair(820,     66),
	make_pair(840,     61),
	make_pair(860,     54),
	make_pair(880,     48),
	make_pair(900,     43),
	make_pair(920,     36),
	make_pair(940,     30)
});
SiliconPhm::SiliconPhm(vector< Pair >&& dimensions, double glue_eff){
	surface=Photosensor(static_right(dimensions),glue_eff,Efficiency.func());
	time_signal=make_shared<WeightedTimeSignal>();
	time_signal->AddSummand(0,1);
	ampl_signal=make_shared<AmplitudeSignal>();
	surface>>time_signal>>ampl_signal;
}
SiliconPhm::~SiliconPhm(){}
shared_ptr< SignalProducent > SiliconPhm::Amplitude(){return ampl_signal;}
shared_ptr< SignalProducent > SiliconPhm::Time(){return time_signal;}
RectDimensions&& SiliconPhm::Dimensions(){return surface->Dimensions();}
void SiliconPhm::Start(){surface->Start();}
void SiliconPhm::RegisterPhoton(Photon& photon){surface->RegisterPhoton(photon);}
void SiliconPhm::End(){surface->End();}
double SiliconPhm::GlueEfficiency(){surface->GlueEfficiency();}
inline vector<Pair> Get_dimensions(Vec&&Center,double hw){
	vector<Pair> result;
	for(double pos:Center)
		result.push_back(make_pair(pos-hw,pos+hw));
	return result;
}
shared_ptr< SiliconPhm > TestPhm(Vec&& center_pos, double width, double glue_eff){
	return shared_ptr<SiliconPhm>(new SiliconPhm(Get_dimensions(static_right(center_pos),width/2.0),glue_eff));
}

shared_ptr<SiliconPhm> Hamamatsu_12572_100P(Vec&& center_pos, double glue_eff){
	return shared_ptr<SiliconPhm>(new SiliconPhm(Get_dimensions(static_right(center_pos),1.5),glue_eff));
}
