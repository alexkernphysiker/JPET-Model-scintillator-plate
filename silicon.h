// this file is distributed under 
// MIT license
#ifndef fYoigiwl
#define fYoigiwl
#include <RectScin/scintillator.h>
#include <RectScin/lightguide.h>
#include <RectScin/sensitive.h>
#include <RectScin/photon2signal.h>
#include <RectScin/signal_processing.h>
namespace Model{
	using namespace std;
	using namespace RectangularScintillator;
	class SiliconPhm:public PhotoSensitiveSurfaceWithTTS{
	public:
		SiliconPhm(vector<Pair>&&dimensions,double glue_eff);
		virtual ~SiliconPhm();
		shared_ptr<SignalProducent> Time();
		shared_ptr<SignalProducent> Amplitude();
	private:
		shared_ptr<WeightedTimeSignal> time_signal;
		shared_ptr<AmplitudeSignal> ampl_signal;
	};
	inline shared_ptr<SiliconPhm> SiPhm(vector<Pair>&&dimensions,double glue_eff){
		return shared_ptr<SiliconPhm>(new SiliconPhm(static_cast<decltype(dimensions)&&>(dimensions),glue_eff));
	}
	class SquaredSilicon:public FlatLightguide{
	public:
		SquaredSilicon(Vec&&pos,double width,double edge, double glue_eff);
		virtual ~SquaredSilicon();
		shared_ptr<SignalProducent> Time();
		shared_ptr<SignalProducent> Amplitude();
	private:
		shared_ptr<SiliconPhm> phm;
	};
	const double Hamamatsu_width=4;
	inline shared_ptr<SquaredSilicon> hamamatsu(Vec&&pos,double glue_eff){
		return shared_ptr<SquaredSilicon>(new SquaredSilicon(static_cast<Vec&&>(pos),Hamamatsu_width,0.5,glue_eff));
	}
	inline shared_ptr<SquaredSilicon> hamamatsu_edgeless(Vec&&pos,double glue_eff){
		return shared_ptr<SquaredSilicon>(new SquaredSilicon(static_cast<Vec&&>(pos),Hamamatsu_width,0.0,glue_eff));
	}
};
#endif