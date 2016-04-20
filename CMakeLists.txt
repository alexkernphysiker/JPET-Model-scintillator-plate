cmake_minimum_required(VERSION 2.6)
project(PlateStecintillator)

add_subdirectory(RectangularScintillator)
include_directories(RectangularScintillator/include)

set(CMAKE_CXX_FLAGS -pthread)
add_definitions(-std=c++11 -Wall -Wunused-parameter)

file(GLOB SOURCES *.cpp)
file(GLOB MODEL model_objects/*.cpp)

add_library(modelfiles SHARED ${MODEL})

foreach(source ${SOURCES})
	get_filename_component(exec ${source} NAME_WE)
	add_executable(${exec} ${source})
	target_link_libraries(${exec} rectscin modelfiles gpwrap)
endforeach()
