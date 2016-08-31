cmake_minimum_required(VERSION 3.0.2)
project(rrcVision CXX)

add_definitions(-std=c++14)

set(DEPENDENT_LIBRARIES OpenCV Boost)

foreach(LIB ${DEPENDENT_LIBRARIES})
    find_package(${LIB} REQUIRED)
    list(APPEND INCLUDE_DIRS ${${LIB}_INCLUDE_DIRS})
    list(APPEND LIBRARIES ${${LIB}_LIBRARIES})
endforeach()

list(APPEND INCLUDE_DIRS include)

file(GLOB INCLUDE include/Line*.h)
file(GLOB SOURCES src/Line*.cpp)

add_library(rrcvision ${INCLUDE} ${SOURCES})
target_link_libraries(rrcvision ${LIBRARIES})
target_include_directories(rrcvision PUBLIC include)

add_executable(rrcVisionDemo demo.cpp)
add_executable(lines exepriments/lines.cpp)
target_link_libraries(lines ${LIBRARIES})
target_link_libraries(rrcVisionDemo rrcvision)
