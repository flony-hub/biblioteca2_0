# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "BibliotecaApp1_0_autogen"
  "CMakeFiles\\BibliotecaApp1_0_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\BibliotecaApp1_0_autogen.dir\\ParseCache.txt"
  )
endif()
