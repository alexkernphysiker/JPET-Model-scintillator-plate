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
