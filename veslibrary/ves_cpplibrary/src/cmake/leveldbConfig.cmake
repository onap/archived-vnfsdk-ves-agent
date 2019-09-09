find_library(LEVELDB_LIBRARY libleveldb.a)
find_path(LEVELDB_INCLUDE_DIR leveldb/db.h)
message("leveldb include dir: ${LEVELDB_INCLUDE_DIR}")
message("leveldb library dir: ${LEVELDB_LIBRARY}")

