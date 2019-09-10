find_library(XTRANSPORT_LIBRARY xtransport ${PROJECT_BINARY_DIR}/lib/transport)
IF(XTRANSPORT_LIBRARY MATCHES "XTRANSPORT_LIBRARY-NOTFOUND")
	set(XTRANSPORT_LIBRARY ${PROJECT_BINARY_DIR}/lib/transport/libxtransport.so)
ENDIF()
find_path(XTRANSPORT_INCLUDE_DIR XTransport.h ${CMAKE_SOURCE_DIR}/lib/transport/include)
message("xtransport include dir: ${XTRANSPORT_INCLUDE_DIR}")
message("xtransport library dir: ${XTRANSPORT_LIBRARY}")

