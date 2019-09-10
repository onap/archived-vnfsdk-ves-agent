find_library(THRIFT_LIBRARY libthrift.a)
find_path(THRIFT_INCLUDE_DIR thrift/Thrift.h)
message("thrift include dir: ${THRIFT_INCLUDE_DIR}")
message("thrift library dir: ${THRIFT_LIBRARY}")

