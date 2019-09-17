find_package(xencode)
find_package(xtransport)
find_package(xlog)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

aux_source_directory(. TEST_SRCS)

include_directories(${XENCODE_INCLUDE_DIR})
include_directories(${XTRANSPORT_INCLUDE_DIR})
include_directories(${XLOG_INCLUDE_DIR})

add_executable(xtest ${TEST_SRCS})

target_link_libraries(xtest ${XENCODE_LIBRARY} ${XTRANSPORT_LIBRARY})

add_custom_command(TARGET xtest
	POST_BUILD
    COMMAND ./test/xtest
	COMMAND gcov -d lib/encode/CMakeFiles/xencode.dir/*.cpp.gcno lib/transport/CMakeFiles/xtransport.dir/*.cpp.gcno lib/encode/CMakeFiles/xencode.dir/__/common/*.cpp.gcno test/CMakeFiles/xtest.dir/*.cpp.gcno
	COMMAND mkdir -p ${COVERAGE_DIR}
	COMMAND mv X*.gcov ${COVERAGE_DIR}/
	COMMAND rm *.gcov -rf
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	)

INSTALL(TARGETS xtest
                RUNTIME DESTINATION bin
)
