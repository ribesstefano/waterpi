cmake_minimum_required(VERSION 3.10)

# Set the project name
project(WaterPi VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(WaterPi ${CMAKE_CURRENT_SOURCE_DIR}/src/waterpi.cpp)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)

# NOTE: an object file becomes a library. All libraries/objects must be LINKED later!
add_subdirectory(${CMAKE_SOURCE_DIR}/src)

# configure_file(TutorialConfig.h.in TutorialConfig.h)
target_include_directories(WaterPi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Locate libraries and headers
# WiringPi
find_package(WiringPi REQUIRED)
# PThreads
find_package(Threads REQUIRED)

# Link against libraries
target_link_libraries(WaterPi ${WIRINGPI_LIBRARIES})
target_link_libraries(WaterPi ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(WaterPi crypt)
target_link_libraries(WaterPi rt)
target_link_libraries(WaterPi m)

target_link_libraries(WaterPi ADC_LIB)
target_link_libraries(WaterPi THERMISTOR_LIB)
target_link_libraries(WaterPi PUMP_LIB)