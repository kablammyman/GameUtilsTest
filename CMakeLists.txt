cmake_minimum_required(VERSION 2.8.9)
project(GameUtilsTest)

set (CMAKE_CXX_STANDARD 11)
IF (APPLE)
	set (CMAKE_CXX_FLAGS "-I/usr/include/i386-linux-gnu/c++/4.8 -I/usr/include/c++/4.8 -I/usr/include/SDL2 -std=c++11 -g3 -Wall -O3")
ELSE ()
	IF (WIN32)
		set (CMAKE_CXX_FLAGS "/D _CRT_SECURE_NO_WARNINGS -W4 /EHsc")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Debug)
	ELSE()
		set (CMAKE_CXX_FLAGS "-I/usr/include/i386-linux-gnu/c++/4.8  -I/usr/include/SDL2 -std=c++11 -pthread -g3 -Wall -O2")
	ENDIF()
ENDIF ()

ADD_SUBDIRECTORY(source)

