// this file is distributed under 
// MIT license
#include "silicon.h"
namespace Model{
	using namespace std;
	using namespace MathTemplates;
	using namespace RectangularScintillator;
	LinearInterpolation<double> Efficiency(Points<double>{
					       point<double>(140,0),
					       point<double>(180,0),
					       point<double>(200,0.33),
					       point<double>(340,0.43),
					       point<double>(380,0.45),
					       point<double>(400,0.49),
					       point<double>(420,0.54),
					       point<double>(440,0.58),
					       point<double>(460,0.64),
					       point<double>(480,0.68),
					       point<double>(500,0.72),
					       point<double>(520,0.73),
					       point<double>(540,0.76),
					       point<double>(560,0.79),
					       point<double>(580,0.82),
					       point<double>(600,0.82),
					       point<double>(620,0.83),
					       point<double>(640,0.84),
					       point<double>(660,0.84),
					       point<double>(680,0.83),
					       point<double>(700,0.82),
					       point<double>(720,0.80),
					       point<double>(740,0.78),
					       point<double>(760,0.75),
					       point<double>(780,0.73),
					       point<double>(800,0.69),
					       point<double>(820,0.66),
					       point<double>(840,0.61),
					       point<double>(860,0.54),
					       point<double>(880,0.48),
					       point<double>(900,0.43),
					       point<double>(920,0.36),
					       point<double>(940,0.30)
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
	}, glue_eff, 1.0, 0.0){
		phm=SiPhm({
			make_pair(pos[0]-(width/2.0-edge),pos[0]+(width/2.0-edge)),
			make_pair(pos[1]-(width/2.0-edge),pos[1]+(width/2.0-edge))
		},1.0);
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
