// this file is distributed under 
// MIT license
#include <math_h/interpolate.h>
#include <math_h/randomfunc.h>
#include "plastic_scin.h"
namespace Model{
	using namespace std;
	using namespace MathTemplates;
	using namespace RectangularScintillator;
	const double refraction=1.58;
	auto LAMBDA=make_shared<DistribTable>(LinearInterpolation<>({
		point<double>(359.686,0.686036),
		point<double>(361.518,1.66851),
		point<double>(363.089,2.79232),
		point<double>(364.66,3.91613),
		point<double>(365.707,5.18177),
		point<double>(367.016,6.44692),
		point<double>(367.801,7.85389),
		point<double>(368.586,8.97918),
		point<double>(370.157,11.6523),
		point<double>(370.681,13.0598),
		point<double>(371.204,14.4672),
		point<double>(371.728,15.7338),
		point<double>(372.251,17.1413),
		point<double>(373.822,23.3355),
		point<double>(374.084,24.7435),
		point<double>(374.346,26.1515),
		point<double>(375.393,33.0509),
		point<double>(375.916,34.4584),
		point<double>(376.178,35.8663),
		point<double>(376.963,42.2029),
		point<double>(377.225,43.6108),
		point<double>(378.796,54.1713),
		point<double>(379.058,55.5792),
		point<double>(380.105,63.0421),
		point<double>(380.366,64.45),
		point<double>(380.628,65.858),
		point<double>(381.675,73.0391),
		point<double>(382.199,74.4466),
		point<double>(382.461,75.8545),
		point<double>(383.246,81.346),
		point<double>(383.508,82.754),
		point<double>(384.031,84.1614),
		point<double>(384.555,85.4281),
		point<double>(385.079,86.8355),
		point<double>(385.602,88.243),
		point<double>(386.649,90.6354),
		point<double>(387.696,91.901),
		point<double>(388.743,93.3075),
		point<double>(390.576,94.29),
		point<double>(392.932,94.426),
		point<double>(394.503,93.4376),
		point<double>(395.812,92.1675),
		point<double>(396.597,90.8984),
		point<double>(398.168,88.2194),
		point<double>(398.691,86.81),
		point<double>(399.215,85.4005),
		point<double>(400,84.1315),
		point<double>(400.524,82.722),
		point<double>(401.309,81.4529),
		point<double>(402.618,78.3519),
		point<double>(403.403,77.0828),
		point<double>(404.188,75.6729),
		point<double>(404.712,74.2635),
		point<double>(405.236,72.854),
		point<double>(405.497,71.4451),
		point<double>(407.33,66.6529),
		point<double>(407.853,65.2435),
		point<double>(408.639,63.9744),
		point<double>(408.901,62.5654),
		point<double>(409.424,61.156),
		point<double>(410.471,58.1963),
		point<double>(410.995,56.7869),
		point<double>(411.518,55.3774),
		point<double>(412.304,54.1083),
		point<double>(413.089,52.8393),
		point<double>(413.874,51.4293),
		point<double>(415.707,48.0456),
		point<double>(416.492,46.6357),
		point<double>(417.277,45.3666),
		point<double>(417.801,43.9572),
		point<double>(418.586,42.6881),
		point<double>(419.372,41.2782),
		point<double>(420.419,38.741),
		point<double>(421.204,37.4719),
		point<double>(421.99,36.062),
		point<double>(422.775,34.6521),
		point<double>(423.822,33.3825),
		point<double>(426.963,28.7287),
		point<double>(428.01,27.4591),
		point<double>(429.058,26.1896),
		point<double>(430.366,24.9195),
		point<double>(431.414,23.6499),
		point<double>(432.723,22.3799),
		point<double>(433.77,21.1103),
		point<double>(435.602,19.2759),
		point<double>(436.911,18.0058),
		point<double>(438.22,16.8766),
		point<double>(439.791,15.7469),
		point<double>(441.361,14.6172),
		point<double>(442.932,13.4875),
		point<double>(443.717,12.9226),
		point<double>(445.288,11.7929),
		point<double>(447.12,10.8035),
		point<double>(448.953,9.53248),
		point<double>(451.047,8.68348),
		point<double>(452.88,7.83497),
		point<double>(454.974,6.98596),
		point<double>(457.33,6.27731),
		point<double>(459.686,5.70951),
		point<double>(462.042,5.00086),
		point<double>(463.089,4.7172),
		point<double>(465.445,4.1494),
		point<double>(467.801,3.72244),
		point<double>(470.157,3.29548),
		point<double>(472.513,2.86852),
		point<double>(475.131,2.58191),
		point<double>(477.487,2.15495),
		point<double>(480.105,2.00919),
		point<double>(481.937,1.86491),
		point<double>(484.293,1.57879),
		point<double>(486.911,1.43303),
		point<double>(489.267,1.14692),
		point<double>(491.885,0.86031),
		point<double>(494.241,0.574196),
		point<double>(496.859,0.428434)
	}));
	LinearInterpolation<double> Absorption(Points<>{
		point<double>(348.842,0.083),
		point<double>(351.158,0.077),
		point<double>(354.247,0.069),
		point<double>(356.564,0.063),
		point<double>(358.88, 0.057),
		point<double>(366.216,0.047),
		point<double>(374.324,0.032),
		point<double>(381.274,0.019),
		point<double>(388.996,0.012),
		point<double>(395.946,0.009),
		point<double>(413.707,0.005),
		point<double>(505.985,0.003),
		point<double>(597.876,0.002),
		point<double>(625.29, 0.002)
	});
	auto time_distr=TimeDistribution2(0.005,0.2,1.5);
	BC420::BC420(const vector<Pair>&dimensions):
	Scintillator(dimensions,refraction,time_distr,LAMBDA,Absorption.func()){}
	BC420::BC420(const vector<Pair>&&dimensions):BC420(dimensions){}
	BC420::~BC420(){}
};
