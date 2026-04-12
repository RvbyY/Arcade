# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/bassirou/delivery/tek2/OOP/arcade/G-OOP-400-STG-4-1-arcade-5/lib/libarcade"
  "/home/bassirou/delivery/tek2/OOP/arcade/G-OOP-400-STG-4-1-arcade-5/libarcade-prefix/src/libarcade-build"
  "/home/bassirou/delivery/tek2/OOP/arcade/G-OOP-400-STG-4-1-arcade-5/libarcade-prefix"
  "/home/bassirou/delivery/tek2/OOP/arcade/G-OOP-400-STG-4-1-arcade-5/libarcade-prefix/tmp"
  "/home/bassirou/delivery/tek2/OOP/arcade/G-OOP-400-STG-4-1-arcade-5/libarcade-prefix/src/libarcade-stamp"
  "/home/bassirou/delivery/tek2/OOP/arcade/G-OOP-400-STG-4-1-arcade-5/libarcade-prefix/src"
  "/home/bassirou/delivery/tek2/OOP/arcade/G-OOP-400-STG-4-1-arcade-5/libarcade-prefix/src/libarcade-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/bassirou/delivery/tek2/OOP/arcade/G-OOP-400-STG-4-1-arcade-5/libarcade-prefix/src/libarcade-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/bassirou/delivery/tek2/OOP/arcade/G-OOP-400-STG-4-1-arcade-5/libarcade-prefix/src/libarcade-stamp${cfgdir}") # cfgdir has leading slash
endif()
