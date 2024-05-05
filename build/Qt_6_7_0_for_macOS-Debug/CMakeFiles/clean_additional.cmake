# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/JaffZork_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/JaffZork_autogen.dir/ParseCache.txt"
  "JaffZork_autogen"
  )
endif()
