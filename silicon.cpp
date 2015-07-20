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
inline vector<Pair> Get100P_dimensions(Vec&&Center,double hw){
	vector<Pair> result;
	for(double pos:Center)
		result.push_back(make_pair(pos-hw,pos+hw));
	return result;
}
SiliconPhm::SiliconPhm(Vec&&center_pos,double hw1,double hw2,double glue_eff,double distance):
FlatLightguide(Get100P_dimensions(static_cast<Vec&&>(center_pos),hw1), glue_eff, 1.0, distance){
	m_silicon=Photosensor(Get100P_dimensions(static_cast<Vec&&>(center_pos),hw2),Efficiency.func(),0.128);
	m_counter=make_shared<Counter>();
	m_timer=make_shared<Timer>(0);
	operator<<(m_silicon<<m_counter<<m_timer);
	m_pos=center_pos;
}
SiliconPhm::~SiliconPhm(){}
Counter&&SiliconPhm::counter(){
	return static_cast<Counter&&>(*m_counter);
}
Timer&& SiliconPhm::timer(){
	return static_cast<Timer&&>(*m_timer);
}
Vec&& SiliconPhm::pos(){
	return static_cast<Vec&&>(m_pos);
}
shared_ptr< SiliconPhm > TestPhm(Vec&& center_pos, double width, double glue_eff, double distance){
	SiliconPhm* res=new SiliconPhm(static_cast<Vec&&>(center_pos),width/2.0,width/2.0,glue_eff,distance);
	return shared_ptr<SiliconPhm>(res);
}

shared_ptr<SiliconPhm> Hamamatsu_12572_100P(Vec&& center_pos, double glue_eff, double distance){
	SiliconPhm* res=new SiliconPhm(static_cast<Vec&&>(center_pos),2.0,1.5,glue_eff,distance);
	return shared_ptr<SiliconPhm>(res);
}
