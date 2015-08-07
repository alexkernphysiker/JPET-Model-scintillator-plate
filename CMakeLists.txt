cmake_minimum_required(VERSION 2.6)
project(PlateStecintillator)
add_subdirectory(RectangularScintillator)
include_directories(RectangularScintillator)
set(CMAKE_CXX_FLAGS "-pthread -std=gnu++11")
set(modelfiles plastic_scin.cpp silicon.cpp RectangularScintillator/math_h/gnuplot/gnuplot.cpp)
#different simulations
add_executable(Model.edges model.phm.edges.cpp ${modelfiles})
target_link_libraries(Model.edges rectscin)
