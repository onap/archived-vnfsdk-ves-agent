cmake_minimum_required (VERSION 2.8)

project (xtest)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(xencode)
find_package(xtransport)
find_package(xlog)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

OPTION (ENABLE_COVERAGE "Use gcov" OFF)
MESSAGE(STATUS ENABLE_COVERAGE=${ENABLE_COVERAGE})
IF(ENABLE_COVERAGE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
ENDIF()

aux_source_directory(. TEST_SRCS)

include_directories(${XENCODE_INCLUDE_DIR})
include_directories(${XTRANSPORT_INCLUDE_DIR})
include_directories(${XLOG_INCLUDE_DIR})

add_executable(xtest ${TEST_SRCS})

target_link_libraries(xtest ${XENCODE_LIBRARY} ${XTRANSPORT_LIBRARY})

INSTALL(TARGETS xtest
                RUNTIME DESTINATION bin
)
