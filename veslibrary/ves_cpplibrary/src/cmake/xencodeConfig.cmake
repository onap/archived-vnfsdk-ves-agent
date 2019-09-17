find_library(XENCODE_LIBRARY xencode ${PROJECT_BINARY_DIR}/lib/encode)
IF(${XENCODE_LIBRARY} MATCHES "XENCODE_LIBRARY-NOTFOUND")
	set(XENCODE_LIBRARY ${PROJECT_BINARY_DIR}/lib/encode/libxencode.so)
ENDIF()
find_path(XENCODE_INCLUDE_DIR XEvent.h ${CMAKE_SOURCE_DIR}/lib/encode/include)
message("xencode include dir: ${XENCODE_INCLUDE_DIR}")
message("xencode library dir: ${XENCODE_LIBRARY}")

