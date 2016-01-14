// this file is distributed under 
// MIT license
#ifndef fYoigiwl
#define fYoigiwl
#include <RectScin/rectscin.h>
#include <RectScin/lightguide.h>
#include <RectScin/sensitive.h>
#include <RectScin/photon2signal.h>
#include <RectScin/signal_processing.h>
class SiliconPhm:public PhotoSensitiveSurfaceWithTTS{
public:
	SiliconPhm(std::vector<Pair>&&dimensions,double glue_eff);
	virtual ~SiliconPhm();
	std::shared_ptr<SignalProducent> Time();
	std::shared_ptr<SignalProducent> Amplitude();
private:
	std::shared_ptr<WeightedTimeSignal> time_signal;
	std::shared_ptr<AmplitudeSignal> ampl_signal;
};
inline std::shared_ptr<SiliconPhm> SiPhm(std::vector<Pair>&&dimensions,double glue_eff){
	return std::shared_ptr<SiliconPhm>(new SiliconPhm(static_cast<decltype(dimensions)&&>(dimensions),glue_eff));
}
class SquaredSilicon:public FlatLightguide{
public:
	SquaredSilicon(Vec&&pos,double width,double edge, double glue_eff);
	virtual ~SquaredSilicon();
	std::shared_ptr<SignalProducent> Time();
	std::shared_ptr<SignalProducent> Amplitude();
private:
	std::shared_ptr<SiliconPhm> phm;
};
const double Hamamatsu_width=4;
inline std::shared_ptr<SquaredSilicon> hamamatsu(Vec&&pos,double glue_eff){
	return std::shared_ptr<SquaredSilicon>(new SquaredSilicon(static_cast<Vec&&>(pos),Hamamatsu_width,0.5,glue_eff));
}
inline std::shared_ptr<SquaredSilicon> hamamatsu_edgeless(Vec&&pos,double glue_eff){
	return std::shared_ptr<SquaredSilicon>(new SquaredSilicon(static_cast<Vec&&>(pos),Hamamatsu_width,0.0,glue_eff));
}
#endif