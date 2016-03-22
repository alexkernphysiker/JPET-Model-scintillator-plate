Library for Monte Carlo simulation of photons movement in scintillator plate with silicon photosensors
======================================================================================================

The programs create multicolumn text files with signals from photomultipliers for further analysis with Irina-qt
(https://github.com/alexkernphysiker/Irina-qt.git)



Compiling
=========

	git clone https://github.com/alexkernphysiker/JPET-Model-scintillator-plate.git
	cd JPET-Model-scintillator-plate
	git submodule update --init --recursive
	cmake .
	make



Directories
===========

	RectangularScintillator
submodule with library for Monte Carlo simulation

	model_object
source of library with classes representing plastic scintillators and silicon photosensors used in current models

	./*.cpp 
files in root directory contain models that are calculated in current model


Models
======

	model.longscin.crosscheck.cpp
model of long scintillator with matrices of hamamatsu silicon photosensors on two it's edges. This is crosscheck for comparing with previous model https://github.com/alexkernphysiker/SiPhmMatrix.git

	model.phm.edged.cpp
model of scintillator plate with four edges covered with hamamatsu silicon photosensors. Calculation is performed for testing spatial resolution of such detector.
