cmake_minimum_required(VERSION 3.10)

# NOTE: Each library/object will have an identifier and that identifier will then
# be used to link the final executable, i.e. target_link_libraries(ProjectName LibraryName)
add_library(ADC_LIB STATIC ${CMAKE_SOURCE_DIR}/src/adc.cpp)
target_include_directories(ADC_LIB PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(THERMISTOR_LIB STATIC ${CMAKE_SOURCE_DIR}/src/adc.cpp)
target_include_directories(THERMISTOR_LIB PUBLIC ${CMAKE_SOURCE_DIR}/include)