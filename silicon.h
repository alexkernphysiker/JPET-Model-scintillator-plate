#ifndef fYoigiwl
#define fYoigiwl
#include <rectscin.h>
#include <sensitive.h>
#include <photon2signal.h>
class SiliconPhm:public IPhotoSensitive{
public:
	SiliconPhm(std::vector<Pair>&&dimensions,double glue_eff);
	virtual ~SiliconPhm();
	std::shared_ptr<SignalProducent> Time();
	std::shared_ptr<SignalProducent> Amplitude();
	virtual void Start()final;
	virtual void RegisterPhoton(Photon&photon)final;
	virtual void End()final;
	virtual RectDimensions&&Dimensions()final;
	virtual double GlueEfficiency()final;
private:
	std::shared_ptr<PhotoSensitiveSurface> surface;
	std::shared_ptr<WeightedTimeSignal> time_signal;
	std::shared_ptr<AmplitudeSignal> ampl_signal;
};
std::shared_ptr<SiliconPhm> TestSquarePhm(Vec&&center_pos,double width,double glue_eff);
std::shared_ptr<SiliconPhm> Hamamatsu_12572_100P(Vec&&center_pos,double glue_eff);
#endif