cmake_minimum_required(VERSION 2.8)
project( testSpeed )

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( testSpeed main.cpp )
target_link_libraries( testSpeed ${OpenCV_LIBS} )