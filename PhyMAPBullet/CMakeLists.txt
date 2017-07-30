#
# Bullet
#
set(BULLET_DIR "C:/Program Files/BULLET_PHYSICS")
include("${BULLET_DIR}/lib/cmake/bullet/BulletConfig.cmake")
include("${BULLET_DIR}/lib/cmake/bullet/UseBullet.cmake")

set(BULLET_COLLISION_LIBRARY "${BULLET_DIR}/lib/Bullet3Collision.lib")
set(BULLET_COLLISION_LIBRARY_DEBUG "${BULLET_DIR}/lib/Bullet3Collision_Debug.lib")
set(BULLET_DYNAMICS_LIBRARY "${BULLET_DIR}/lib/Bullet3Dynamics.lib")
set(BULLET_DYNAMICS_LIBRARY_DEBUG "${BULLET_DIR}/lib/Bullet3Dynamics_Debug.lib")
set(BULLET_MATH_LIBRARY "${BULLET_ROOT_DIR}/lib/LinearMath.lib")
set(BULLET_MATH_LIBRARY_DEBUG "${BULLET_ROOT_DIR}/lib/LinearMath_Debug.lib")
set(BULLET_COMMON_LIBRARY "${BULLET_DIR}/lib/Bullet3Common.lib")
set(BULLET_COMMON_LIBRARY_DEBUG "${BULLET_DIR}/lib/Bullet3Common_Debug.lib")
set(BULLET_GEOMETRY_LIBRARY "${BULLET_DIR}/lib/Bullet3Geometry.lib")
set(BULLET_GEOMETRY_LIBRARY_DEBUG "${BULLET_DIR}/lib/Bullet3Geometry_Debug.lib")
set(BULLET_FILE_LIBRARY "${BULLET_DIR}/lib/Bullet2FileLoader.lib")
set(BULLET_FILE_LIBRARY_DEBUG "${BULLET_DIR}/lib/Bullet2FileLoader_Debug.lib")
set(BULLET_IMPORTER_LIBRARY "${BULLET_DIR}/lib/BulletWorldImporter.lib")
set(BULLET_IMPORTER_LIBRARY_DEBUG "${BULLET_DIR}/lib/BulletWorldImporter_Debug.lib")
set(BULLET_COLLISION0_LIBRARY "${BULLET_DIR}/lib/BulletCollision.lib")
set(BULLET_COLLISION0_LIBRARY_DEBUG "${BULLET_DIR}/lib/BulletCollision_Debug.lib")
set(BULLET_DYNAMICS0_LIBRARY "${BULLET_DIR}/lib/BulletDynamics.lib")
set(BULLET_DYNAMICS0_LIBRARY_DEBUG "${BULLET_DIR}/lib/BulletDynamics_Debug.lib")


# Avoid source tree pollution
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
	message(FATAL_ERROR "In-source builds are not permitted. Make a separate folder for building:\nmkdir build; cd build; cmake ..\nBefore that, remove the files already created:\nrm -rf CMakeCache.txt CMakeFiles")
endif(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)

message(STATUS "===")
message(STATUS ${CMAKE_MODULE_PATH})
message(STATUS "===")
 
if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif (CMAKE_BUILD_TYPE STREQUAL "")

set(CMAKE_DEBUG_POSTFIX "_d")

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}")

# Specify build paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
if (WIN32 OR APPLE)
  if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    # We don't want to install in default system location, install is really for the SDK, so call it that
    set(CMAKE_INSTALL_PREFIX
	  "${CMAKE_BINARY_DIR}/${PROJECT_NAME}" CACHE PATH "${PROJECT_NAME} install prefix" FORCE
    )
  endif (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
endif(WIN32 OR APPLE)

#
# build property
#
add_definitions(-DBULLET_LIBRARY_EXPORTS -DCOMMON_LIBRARY_IMPORTS)
#add_definitions(-D_HAS_ITERATOR_DEBUGGING=0 -D_ITERATOR_DEBUG_LEVEL=0 -D_CRT_SECURE_NO_WARNINGS)

# Activate C++ exception handling
IF (NOT CMAKE_CXX_FLAGS MATCHES "/EHsc")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHa") 
ENDIF ()
IF (NOT CMAKE_CXX_FLAGS MATCHES "/MP")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP") 
ENDIF ()
IF (NOT CMAKE_CXX_FLAGS MATCHES "-Zm")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Zm300") 
ENDIF ()

FILE(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
FILE(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
FILE(GLOB_RECURSE RC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.rc)
FILE(GLOB_RECURSE ICO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.ico)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/../PhyMAPCommon/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${BULLET_ROOT_DIR}/include
  ${BULLET_ROOT_DIR}/include/bullet
)

add_library(PhyMAPBullet ${SOURCE_FILES} ${HEADER_FILES} ${RC_FILES} ${ICO_FILES})

target_link_libraries(PhyMAPBullet PhyMAPCommon)
target_link_libraries(PhyMAPBullet
    debug ${BULLET_COLLISION_LIBRARY_DEBUG}
    debug ${BULLET_DYNAMICS_LIBRARY_DEBUG}
    debug ${BULLET_MATH_LIBRARY_DEBUG}
    debug ${BULLET_COMMON_LIBRARY_DEBUG}
    debug ${BULLET_GEOMETRY_LIBRARY_DEBUG}
    debug ${BULLET_FILE_LIBRARY_DEBUG}
    debug ${BULLET_IMPORTER_LIBRARY_DEBUG}
    debug ${BULLET_COLLISION0_LIBRARY_DEBUG}
    debug ${BULLET_DYNAMICS0_LIBRARY_DEBUG}
		
	optimized ${BULLET_COLLISION_LIBRARY}
    optimized ${BULLET_DYNAMICS_LIBRARY}
    optimized ${BULLET_MATH_LIBRARY}
    optimized ${BULLET_COMMON_LIBRARY}
    optimized ${BULLET_GEOMETRY_LIBRARY}
    optimized ${BULLET_FILE_LIBRARY}
    optimized ${BULLET_IMPORTER_LIBRARY}
    optimized ${BULLET_COLLISION0_LIBRARY}
    optimized ${BULLET_DYNAMICS0_LIBRARY}
)

#
# cotire
#
add_definitions(-DCOTIRE_MINIMUM_NUMBER_OF_TARGET_SOURCES=1)
set_directory_properties(PROPERTIES
  COTIRE_PREFIX_HEADER_IGNORE_PATH 
  "${PROJECT_SOURCE_DIR}"
)
set_target_properties(PhyMAPBullet PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
cotire(PhyMAPBullet CONFIGURATIONS ${CMAKE_BUILD_TYPE})

