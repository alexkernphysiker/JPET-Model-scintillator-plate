cmake_minimum_required(VERSION 2.6)
project(PlateStecintillator)
add_definitions(-std=c++17)

add_subdirectory(math_h)
include_directories(${MATH_H_INC})
add_subdirectory(RectangularScintillator)
include_directories(${RECTSCIN_INC})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
file(GLOB MODEL model_objects/*.cpp)
add_library(modelfiles SHARED ${MODEL})
file(GLOB SOURCES *.cpp)
foreach(source ${SOURCES})
	get_filename_component(exec ${source} NAME_WE)
	add_executable(${exec} ${source})
	target_link_libraries(${exec} rectscin modelfiles)
endforeach()
