// this file is distributed under 
// GPL v 3.0 license
#ifndef fYoigiwl
#define fYoigiwl
#include <rectscin.h>
#include <sensitive.h>
#include <photon2signal.h>
#include <signal_processing.h>
class SiliconPhm:public PhotoSensitiveSurface{
public:
	SiliconPhm(std::vector<Pair>&&dimensions,double glue_eff);
	virtual ~SiliconPhm();
	std::shared_ptr<SignalProducent> Time();
	std::shared_ptr<SignalProducent> Amplitude();
private:
	std::shared_ptr<WeightedTimeSignal> time_signal;
	std::shared_ptr<SignalSmear> tts;
	std::shared_ptr<AmplitudeSignal> ampl_signal;
};
inline std::shared_ptr<SiliconPhm> SiPhm(std::vector<Pair>&&dimensions,double glue_eff){
	return std::shared_ptr<SiliconPhm>(new SiliconPhm(static_right(dimensions),glue_eff));
}
#endif