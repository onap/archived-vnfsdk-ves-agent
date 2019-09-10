aux_source_directory(../common LOG_SRCS)
aux_source_directory(. ENCODE_SRCS)

find_package(nlohmann_json REQUIRED)
find_package(spdlog REQUIRED)

include_directories(include)

add_library(xencode SHARED ${LOG_SRCS} ${ENCODE_SRCS})

file(GLOB HDRS "include/*.h")

install(FILES ${HDRS}
	    DESTINATION "include/xvesagent/xencode"
)
install(FILES ../../cmake/xencodeConfig.cmake
	    DESTINATION "lib/cmake/xencode"
)
INSTALL(TARGETS xencode
	LIBRARY DESTINATION lib
)
