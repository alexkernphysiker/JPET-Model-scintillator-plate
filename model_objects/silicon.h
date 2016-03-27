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
	class SiliconPhm:public RectangularScintillator::PhotoSensitiveSurfaceWithTTS{
	public:
		SiliconPhm(const std::vector<RectangularScintillator::Pair>&dimensions,const double glue_eff);
		virtual ~SiliconPhm();
		const std::shared_ptr<RectangularScintillator::SignalProducent> Time()const;
		const std::shared_ptr<RectangularScintillator::SignalProducent> Amplitude()const;
	private:
		std::shared_ptr<RectangularScintillator::WeightedTimeSignal> time_signal;
		std::shared_ptr<RectangularScintillator::AmplitudeSignal> ampl_signal;
	};
	inline const std::shared_ptr<SiliconPhm> SiPhm(const std::vector<RectangularScintillator::Pair>&&dimensions,const double glue_eff){
		return std::shared_ptr<SiliconPhm>(new SiliconPhm(dimensions,glue_eff));
	}
	class SquaredSilicon:public RectangularScintillator::FlatLightguide{
	public:
		SquaredSilicon(const RectangularScintillator::Vec&pos,const double width,const double edge,const double glue_eff);
		virtual ~SquaredSilicon();
		const std::shared_ptr<RectangularScintillator::SignalProducent> Time()const;
		const std::shared_ptr<RectangularScintillator::SignalProducent> Amplitude()const;
	private:
		std::shared_ptr<SiliconPhm> phm;
	};
	inline const std::shared_ptr<SquaredSilicon> hamamatsu(const RectangularScintillator::Vec&&pos,const double glue_eff){
		return std::shared_ptr<SquaredSilicon>(new SquaredSilicon(pos,4,0.5,glue_eff));
	}
	inline const std::shared_ptr<SquaredSilicon> hamamatsu_edgeless(const RectangularScintillator::Vec&&pos,const double glue_eff){
		return std::shared_ptr<SquaredSilicon>(new SquaredSilicon(pos,4,0.0,glue_eff));
	}
};
#endif