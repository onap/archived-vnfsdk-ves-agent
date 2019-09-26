find_library(XTRANSPORT_LIBRARY xtransport /usr/lib /usr/lib64 /usr/local/lib /usr/local/lib64 ${PROJECT_BINARY_DIR}/lib/transport)
IF(XTRANSPORT_LIBRARY MATCHES "XTRANSPORT_LIBRARY-NOTFOUND")
	set(XTRANSPORT_LIBRARY ${PROJECT_BINARY_DIR}/lib/transport/libxtransport.so)
ENDIF()
find_path(XTRANSPORT_INCLUDE_DIR XTransport.h /usr/include/xvesagent/xtransport /usr/local/include/xvesagent/xtransport ${CMAKE_SOURCE_DIR}/lib/transport/include)
message("xtransport include dir: ${XTRANSPORT_INCLUDE_DIR}")
message("xtransport library dir: ${XTRANSPORT_LIBRARY}")

