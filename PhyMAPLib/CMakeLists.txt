

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
#add_definitions(-D_HAS_ITERATOR_DEBUGGING=0 -D_ITERATOR_DEBUG_LEVEL=0 -D_CRT_SECURE_NO_WARNINGS)
add_definitions(-DBULLET_LIBRARY_IMPORTS)
add_definitions(-DCOMMON_LIBRARY_IMPORTS)
add_definitions(-D_WINDLL)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

# Activate C++ exception handling
#IF (NOT CMAKE_CXX_FLAGS MATCHES "/EHsc")
#  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHa") 
#ENDIF ()
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
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/../PhyMAPCommon/include
  ${CMAKE_CURRENT_SOURCE_DIR}/../PhyMAPBullet/include
#  #${BULLET_ROOT_DIR}/include
#  #${BULLET_ROOT_DIR}/include/bullet
)

add_library(PhyMAPLib SHARED ${SOURCE_FILES} ${HEADER_FILES} ${RC_FILES} ${ICO_FILES})
set_source_files_properties(${SOURCE_FILES} ${HEADER_FILES} ${RC_FILES} ${ICO_FILES} PROPERTIES COMPILE_FLAGS "/CLR /TP") 

set(CMAKE_EXE_LINKER_FLAGS
      "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:LIBCMT")

SET_TARGET_PROPERTIES(PhyMAPLib PROPERTIES COMPILE_FLAGS "/clr")  
SET_TARGET_PROPERTIES(PhyMAPLib PROPERTIES LINKER_LANGUAGE CXX)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /FU\"c:\\Program Files (x86)\\Rhinoceros 5\\System\\RhinoCommon.dll\" ")

if(CMAKE_CXX_FLAGS_DEBUG MATCHES "/RTC1")
   string(REPLACE "/RTC1" " " CMAKE_CXX_FLAGS_DEBUG 
"${CMAKE_CXX_FLAGS_DEBUG}")
   message(STATUS PhyMAPLib  " CMAKE_CXX_FLAGS_DEBUG removing /RTC1")
endif()

if(CMAKE_CXX_FLAGS MATCHES "/EHsc")
   string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
   message(STATUS PhyMAPLib  " CMAKE_CXX_FLAGS removing /EHsc")
endif()

if(CMAKE_CXX_FLAGS MATCHES "/MD")
   string(REPLACE "/MDd" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

target_link_libraries(PhyMAPLib PhyMAPBullet)


#
# copying
#
add_custom_command(TARGET PhyMAPLib POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy 
     "$<TARGET_FILE:PhyMAPLib>"
     "${CMAKE_BINARY_DIR}/bin/PhyMAPLib.dll" 
  COMMENT ":::Copying:::")

#
# cotire
#
add_definitions(-DCOTIRE_MINIMUM_NUMBER_OF_TARGET_SOURCES=1)
set_directory_properties(PROPERTIES
  COTIRE_PREFIX_HEADER_IGNORE_PATH 
  "${PROJECT_SOURCE_DIR}"
)
set_target_properties(PhyMAPLib PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
cotire(PhyMAPLib CONFIGURATIONS ${CMAKE_BUILD_TYPE})




