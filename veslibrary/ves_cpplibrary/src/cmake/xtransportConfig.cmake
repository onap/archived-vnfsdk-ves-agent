find_library(XTRANSPORT_LIBRARY xtransport)
find_path(XTRANSPORT_INCLUDE_DIR xvesagent/xtransport/XTransport.h)
set(XTRANSPORT_INCLUDE_DIR "${XTRANSPORT_INCLUDE_DIR}/xvesagent/xtransport")
message("xtransport include dir: ${XTRANSPORT_INCLUDE_DIR}")
message("xtransport library dir: ${XTRANSPORT_LIBRARY}")

