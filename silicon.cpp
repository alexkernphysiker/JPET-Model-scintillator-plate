#include "silicon.h"
using namespace std;
double GetSiliconEfficiency(double lambda){
	static vector<double> data={
		140,     0,
		160,     0,
		180,     0,
		200,     33,
		340,     43,
		380,     45,
		400,     49,
		420,     54,
		440,     58,
		460,     64,
		480,     68,
		500,     72,
		520,     73,
		540,     76,
		560,     79,
		580,     82,
		600,     82,
		620,     83,
		640,     84,
		660,     84,
		680,     83,
		700,     82,
		720,     80,
		740,     78,
		760,     75,
		780,     73,
		800,     69,
		820,     66,
		840,     61,
		860,     54,
		880,     48,
		900,     43,
		920,     36,
		940,     30
	};
	static LinearInterpolation<double> interpolate;
	if(interpolate.size()==0)
		for(int i=0,n=data.size()-1;i<n;i+=2)
			interpolate<<make_pair(data[i],data[i+1]/100.0);
		return interpolate(lambda);
}
inline vector<Pair> Get100P_dimensions(Vec&&Center,double hw){
	vector<Pair> result;
	for(double pos:Center)
		result.push_back(make_pair(pos-hw,pos+hw));
	return result;
}
SiliconPhm::SiliconPhm(Vec&&center_pos,double hw1,double hw2,double glue_eff,double distance):
FlatLightguide(Get100P_dimensions(static_cast<Vec&&>(center_pos),hw1), glue_eff, 1.0, distance){
	m_silicon=Photosensor(Get100P_dimensions(static_cast<Vec&&>(center_pos),hw2),GetSiliconEfficiency,0.128);
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
