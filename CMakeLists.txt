cmake_minimum_required(VERSION 3.0.2)

project(PhyMAP)
set(CMAKE_BUILD_TYPE "Debug;Release")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake;${CMAKE_MODULE_PATH}")
include(cotire) 

add_subdirectory(${CMAKE_SOURCE_DIR}/PhyMAPCommon)
add_subdirectory(${CMAKE_SOURCE_DIR}/PhyMAPLib)
add_subdirectory(${CMAKE_SOURCE_DIR}/PhyMAPBullet)
add_subdirectory(${CMAKE_SOURCE_DIR}/PhyMAPComponent)

add_dependencies(PhyMAPLib PhyMAPCommon)
add_dependencies(PhyMAPLib PhyMAPBullet)
add_dependencies(PhyMAPComponent PhyMAPLib)
