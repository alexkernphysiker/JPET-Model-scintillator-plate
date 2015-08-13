// this file is distributed under
// GPL v 3.0 license
#include <iostream>
#include <sstream>
#include <signal_processing.h>
#include <signal_statistics.h>
#include "plastic_scin.h"
#include "silicon.h"
using namespace std;
#include "model.params.cc"
Vec PhmStep={Hamamatsu::Width(),Hamamatsu::Width(),Hamamatsu::Width()};
int main(int,char**){
	RANDOM engine;
	BC420 scintillator({make_pair(0,ScinSize[0]),make_pair(0,ScinSize[1]),make_pair(0,ScinSize[2])});
}