cmake_minimum_required (VERSION 2.8)

project (xvesagent)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x") 

OPTION (ENABLE_COVERAGE "Use coverage" OFF)
MESSAGE(STATUS ENABLE_COVERAGE=${ENABLE_COVERAGE})

iF(NOT DEFINED COVERAGE_DIR)
	set(COVERAGE_DIR "coverage")
ENDIF()

MESSAGE(STATUS COVERAGE_DIR=${COVERAGE_DIR})

IF(ENABLE_COVERAGE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
	add_subdirectory(test)
	add_dependencies(xtest xencode xtransport)
ENDIF()

add_subdirectory(lib)

