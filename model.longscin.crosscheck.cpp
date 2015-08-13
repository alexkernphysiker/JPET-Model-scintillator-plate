// this file is distributed under
// GPL v 3.0 license
#include <iostream>
#include <sstream>
#include <signal_processing.h>
#include <signal_statistics.h>
#include "plastic_scin.h"
#include "silicon.h"
using namespace std;
int main(int,char**){
	RANDOM engine;
	BC420 scintillator({make_pair(-150,150),make_pair(-9.5,9.5),make_pair(-3.5,3.5)});
}