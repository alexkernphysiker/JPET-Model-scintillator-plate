// this file is distributed under 
// MIT license
#include "silicon.h"
namespace Model{
	using namespace std;
	using namespace MathTemplates;
	using namespace RectangularScintillator;
	LinearInterpolation<double> Efficiency({
					       make_pair(140,0),
					       make_pair(180,0),
					       make_pair(200,0.33),
					       make_pair(340,0.43),
					       make_pair(380,0.45),
					       make_pair(400,0.49),
					       make_pair(420,0.54),
					       make_pair(440,0.58),
					       make_pair(460,0.64),
					       make_pair(480,0.68),
					       make_pair(500,0.72),
					       make_pair(520,0.73),
					       make_pair(540,0.76),
					       make_pair(560,0.79),
					       make_pair(580,0.82),
					       make_pair(600,0.82),
					       make_pair(620,0.83),
					       make_pair(640,0.84),
					       make_pair(660,0.84),
					       make_pair(680,0.83),
					       make_pair(700,0.82),
					       make_pair(720,0.80),
					       make_pair(740,0.78),
					       make_pair(760,0.75),
					       make_pair(780,0.73),
					       make_pair(800,0.69),
					       make_pair(820,0.66),
					       make_pair(840,0.61),
					       make_pair(860,0.54),
					       make_pair(880,0.48),
					       make_pair(900,0.43),
					       make_pair(920,0.36),
					       make_pair(940,0.30)
	});
	SiliconPhm::SiliconPhm(const vector< Pair >&dimensions,const double glue_eff):PhotoSensitiveSurfaceWithTTS(dimensions,glue_eff,Efficiency.func(),0.128){
		time_signal=make_shared<WeightedTimeSignal>();
		time_signal->AddSummand(0,1);
		ampl_signal=make_shared<AmplitudeSignal>();
		operator>>(time_signal)>>ampl_signal;
	}
	SiliconPhm::~SiliconPhm(){}
	const shared_ptr< SignalProducent > SiliconPhm::Amplitude()const{return ampl_signal;}
	const shared_ptr< SignalProducent > SiliconPhm::Time()const{return time_signal;}
	
	SquaredSilicon::SquaredSilicon(const Vec&pos,const double width,const double edge,const double glue_eff)
	:FlatLightguide({
		make_pair(pos[0]-(width/2.0),pos[0]+(width/2.0)),
		make_pair(pos[1]-(width/2.0),pos[1]+(width/2.0))
	}, glue_eff, 1, 0){
		phm=SiPhm({
			make_pair(pos[0]-(width/2.0-edge),pos[0]+(width/2.0-edge)),
			make_pair(pos[1]-(width/2.0-edge),pos[1]+(width/2.0-edge))
		},1);
		operator>>(phm);
	}
	SquaredSilicon::~SquaredSilicon(){}
	const shared_ptr< SignalProducent > SquaredSilicon::Amplitude()const{
		return phm->Amplitude();
	}
	const shared_ptr< SignalProducent > SquaredSilicon::Time()const{
		return phm->Time();
	}
};