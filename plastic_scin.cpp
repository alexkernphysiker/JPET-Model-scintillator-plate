#include <math_h/gnuplot/gnuplot.h>
#include <math_h/interpolate.h>
#include <math_h/randomfunc.h>
#include "plastic_scin.h"
using namespace std;
const double refraction=1.58;
LinearInterpolation<double> LAMBDA({
	make_pair(359.686,0.686036),
	make_pair(361.518,1.66851),
	make_pair(363.089,2.79232),
	make_pair(364.66,3.91613),
	make_pair(365.707,5.18177),
	make_pair(367.016,6.44692),
	make_pair(367.801,7.85389),
	make_pair(368.586,8.97918),
	make_pair(370.157,11.6523),
	make_pair(370.681,13.0598),
	make_pair(371.204,14.4672),
	make_pair(371.728,15.7338),
	make_pair(372.251,17.1413),
	make_pair(373.822,23.3355),
	make_pair(374.084,24.7435),
	make_pair(374.346,26.1515),
	make_pair(375.393,33.0509),
	make_pair(375.916,34.4584),
	make_pair(376.178,35.8663),
	make_pair(376.963,42.2029),
	make_pair(377.225,43.6108),
	make_pair(378.796,54.1713),
	make_pair(379.058,55.5792),
	make_pair(380.105,63.0421),
	make_pair(380.366,64.45),
	make_pair(380.628,65.858),
	make_pair(381.675,73.0391),
	make_pair(382.199,74.4466),
	make_pair(382.461,75.8545),
	make_pair(383.246,81.346),
	make_pair(383.508,82.754),
	make_pair(384.031,84.1614),
	make_pair(384.555,85.4281),
	make_pair(385.079,86.8355),
	make_pair(385.602,88.243),
	make_pair(386.649,90.6354),
	make_pair(387.696,91.901),
	make_pair(388.743,93.3075),
	make_pair(390.576,94.29),
	make_pair(392.932,94.426),
	make_pair(394.503,93.4376),
	make_pair(395.812,92.1675),
	make_pair(396.597,90.8984),
	make_pair(398.168,88.2194),
	make_pair(398.691,86.81),
	make_pair(399.215,85.4005),
	make_pair(400,84.1315),
	make_pair(400.524,82.722),
	make_pair(401.309,81.4529),
	make_pair(402.618,78.3519),
	make_pair(403.403,77.0828),
	make_pair(404.188,75.6729),
	make_pair(404.712,74.2635),
	make_pair(405.236,72.854),
	make_pair(405.497,71.4451),
	make_pair(407.33,66.6529),
	make_pair(407.853,65.2435),
	make_pair(408.639,63.9744),
	make_pair(408.901,62.5654),
	make_pair(409.424,61.156),
	make_pair(410.471,58.1963),
	make_pair(410.995,56.7869),
	make_pair(411.518,55.3774),
	make_pair(412.304,54.1083),
	make_pair(413.089,52.8393),
	make_pair(413.874,51.4293),
	make_pair(415.707,48.0456),
	make_pair(416.492,46.6357),
	make_pair(417.277,45.3666),
	make_pair(417.801,43.9572),
	make_pair(418.586,42.6881),
	make_pair(419.372,41.2782),
	make_pair(420.419,38.741),
	make_pair(421.204,37.4719),
	make_pair(421.99,36.062),
	make_pair(422.775,34.6521),
	make_pair(423.822,33.3825),
	make_pair(426.963,28.7287),
	make_pair(428.01,27.4591),
	make_pair(429.058,26.1896),
	make_pair(430.366,24.9195),
	make_pair(431.414,23.6499),
	make_pair(432.723,22.3799),
	make_pair(433.77,21.1103),
	make_pair(435.602,19.2759),
	make_pair(436.911,18.0058),
	make_pair(438.22,16.8766),
	make_pair(439.791,15.7469),
	make_pair(441.361,14.6172),
	make_pair(442.932,13.4875),
	make_pair(443.717,12.9226),
	make_pair(445.288,11.7929),
	make_pair(447.12,10.8035),
	make_pair(448.953,9.53248),
	make_pair(451.047,8.68348),
	make_pair(452.88,7.83497),
	make_pair(454.974,6.98596),
	make_pair(457.33,6.27731),
	make_pair(459.686,5.70951),
	make_pair(462.042,5.00086),
	make_pair(463.089,4.7172),
	make_pair(465.445,4.1494),
	make_pair(467.801,3.72244),
	make_pair(470.157,3.29548),
	make_pair(472.513,2.86852),
	make_pair(475.131,2.58191),
	make_pair(477.487,2.15495),
	make_pair(480.105,2.00919),
	make_pair(481.937,1.86491),
	make_pair(484.293,1.57879),
	make_pair(486.911,1.43303),
	make_pair(489.267,1.14692),
	make_pair(491.885,0.86031),
	make_pair(494.241,0.574196),
	make_pair(496.859,0.428434)
});
LinearInterpolation<double> Absorption({
	make_pair(348.842,0.083),
	make_pair(351.158,0.077),
	make_pair(354.247,0.069),
	make_pair(356.564,0.063),
	make_pair(358.88, 0.057),
	make_pair(366.216,0.047),
	make_pair(374.324,0.032),
	make_pair(381.274,0.019),
	make_pair(388.996,0.012),
	make_pair(395.946,0.009),
	make_pair(413.707,0.005),
	make_pair(505.985,0.003),
	make_pair(597.876,0.002),
	make_pair(625.29, 0.002)
});
RandomValueGenerator<double> GetLambdaDistribution(){
	RandomValueGenerator<double> gen([LAMBDA](double lambda){return LAMBDA(lambda);},LAMBDA.min(),LAMBDA.max(),200);
	return gen;
}
BC420::BC420(vector<Pair>&&dimensions):
	RectangularScintillator(
		static_left(dimensions),
		TimeDistribution2(0.005,0.2,1.5),
		GetLambdaDistribution(),
		refraction,Absorption.func()
	){
}
BC420::~BC420(){}