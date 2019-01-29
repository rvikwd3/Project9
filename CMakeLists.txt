cmake_minimum_required(VERSION 2.8)
project(Project9)

# Include the Boost library
find_package( Boost 1.40 COMPONENTS program_options REQUIRED )
include_directories( ${Boost_INCLUDE_DIR} )
# Include the header files in include/
include_directories(include)

# Run `Magick++-config --cxxflags --libs` and include them in the compiler
# Replaces g++ `Magick++-config --cppflags --cxxflags --ldflags --libs` 
find_program( MAGICK_CONFIG "Magick++-config" )
execute_process( COMMAND "${MAGICK_CONFIG}" "--cxxflags" OUTPUT_VARIABLE MAGICK_CXX_FLAGS )
execute_process( COMMAND "${MAGICK_CONFIG}" "--libs" OUTPUT_VARIABLE MAGICK_LD_FLAGS )
# Strip trailing whitespace from flags
string( STRIP "${MAGICK_CXX_FLAGS}" MAGICK_CXX_FLAGS )
string( STRIP "${MAGICK_LD_FLAGS}" MAGICK_LD_FLAGS )
# Append Magick++ flags to existing flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ${MAGICK_CXX_FLAGS} ${MAGICK_LD_FLAGS}")

set (SOURCES src/main.cpp src/convert.cpp src/magick.cpp src/options.cpp src/imagematrix.cpp)

add_executable(Project9 ${SOURCES})

target_link_libraries( Project9 LINK_PUBLIC ${Boost_LIBRARIES} )
