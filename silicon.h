#ifndef fYoigiwl
#define fYoigiwl
#include <rectscin.h>
#include <lightguide.h>
#include <sensitive.h>
#include <signal_model.h>
class SiliconPhm:public FlatLightguide{
public:
	SiliconPhm(Vec&&center_pos, double hw_all, double hw_sensitive,double glue_eff,double distance);
	virtual ~SiliconPhm();
	Counter&&counter();
	Timer&&timer();
	Vec&&pos();
private:
	Vec m_pos;
	std::shared_ptr<PhotoSensitiveSurfaceWithTTS> m_silicon;
	std::shared_ptr<Counter> m_counter;
	std::shared_ptr<Timer> m_timer;
};
std::shared_ptr<SiliconPhm> TestPhm(Vec&&center_pos,double width,double glue_eff=0,double distance=0);
std::shared_ptr<SiliconPhm> Hamamatsu_12572_100P(Vec&&center_pos,double glue_eff=0,double distance=0);
#endif