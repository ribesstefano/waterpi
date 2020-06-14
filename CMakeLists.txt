cmake_minimum_required(VERSION 3.10)

# set the project name
project(WaterPi VERSION 1.0)

# # add the executable
# add_executable(WaterPi tutorial.cxx)
SET(GCC_COVERAGE_COMPILE_FLAGS "")
SET(GCC_COVERAGE_LINK_FLAGS    "-lwiringPi -lpthread -lm -lcrypt -lrt")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# configure_file(TutorialConfig.h.in TutorialConfig.h)
target_include_directories(WaterPi PUBLIC "${PROJECT_BINARY_DIR}/include")