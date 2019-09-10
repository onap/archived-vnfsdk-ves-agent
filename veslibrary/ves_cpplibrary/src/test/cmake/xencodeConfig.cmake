find_library(XENCODE_LIBRARY xencode)
find_path(XENCODE_INCLUDE_DIR xvesagent/xencode/XEvent.h)
set(XENCODE_INCLUDE_DIR "${XENCODE_INCLUDE_DIR}/xvesagent/xencode")
message("xencode include dir: ${XENCODE_INCLUDE_DIR}")
message("xencode library dir: ${XENCODE_LIBRARY}")

