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
		SiliconPhm(const vector<Pair>&dimensions,const double glue_eff);
		virtual ~SiliconPhm();
		const shared_ptr<SignalProducent> Time()const;
		const shared_ptr<SignalProducent> Amplitude()const;
	private:
		shared_ptr<WeightedTimeSignal> time_signal;
		shared_ptr<AmplitudeSignal> ampl_signal;
	};
	inline const shared_ptr<SiliconPhm> SiPhm(const vector<Pair>&&dimensions,const double glue_eff){
		return shared_ptr<SiliconPhm>(new SiliconPhm(dimensions,glue_eff));
	}
	class SquaredSilicon:public FlatLightguide{
	public:
		SquaredSilicon(const Vec&pos,const double width,const double edge,const double glue_eff);
		virtual ~SquaredSilicon();
		const shared_ptr<SignalProducent> Time()const;
		const shared_ptr<SignalProducent> Amplitude()const;
	private:
		shared_ptr<SiliconPhm> phm;
	};
	inline const shared_ptr<SquaredSilicon> hamamatsu(const Vec&&pos,const double glue_eff){
		return shared_ptr<SquaredSilicon>(new SquaredSilicon(pos,4,0.5,glue_eff));
	}
	inline const shared_ptr<SquaredSilicon> hamamatsu_edgeless(const Vec&&pos,const double glue_eff){
		return shared_ptr<SquaredSilicon>(new SquaredSilicon(pos,4,0.0,glue_eff));
	}
};
#endif