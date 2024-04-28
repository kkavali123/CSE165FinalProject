# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\CSE165Project3_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\CSE165Project3_autogen.dir\\ParseCache.txt"
  "CSE165Project3_autogen"
  )
endif()
