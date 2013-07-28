project(bzip2)
add_definitions(-D_FILE_OFFSET_BITS=64)
add_library(cmbzip2
  blocksort.c huffman.c crctable.c randtable.c compress.c decompress.c bzlib.c)
set_target_properties(cmbzip2 PROPERTIES POSITION_INDEPENDENT_CODE 1)
