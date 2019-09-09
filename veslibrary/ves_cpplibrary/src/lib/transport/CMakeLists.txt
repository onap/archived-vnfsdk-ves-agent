aux_source_directory(../common LOG_SRCS)
aux_source_directory(. TRANSPORT_SRCS)
aux_source_directory(gen-cpp RPC_SRCS)

find_package(nlohmann_json)
find_package(spdlog)
find_package(leveldb)
find_package(thrift)
find_package(CURL)

include_directories("${THRIFT_INCLUDE_DIR}")
include_directories("${LEVELDB_INCLUDE_DIR}")
include_directories(include)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")

add_library(xtransport SHARED ${LOG_SRCS} ${RPC_SRCS} ${TRANSPORT_SRCS})
target_link_libraries(xtransport ${CURL_LIBRARY} ${THRIFT_LIBRARY} ${LEVELDB_LIBRARY})

file(GLOB HDRS "include/*.h")

install(FILES ${HDRS}
	    DESTINATION "include/xvesagent/xtransport"
)
install(FILES ../../cmake/xtransportConfig.cmake
	    DESTINATION "lib/cmake/xtransport"
)
INSTALL(TARGETS xtransport
	LIBRARY DESTINATION lib
)
