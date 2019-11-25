# CMakeList.txt : CMake project for Service, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project (interview-service C CXX)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
#
# JSON
#
include_directories (BEFORE SYSTEM ${CMAKE_SOURCE_DIR}/lib/json/include)

cmake_policy(SET CMP0074 NEW)

set(Boost_USE_STATIC_LIBS        ON)

find_package(Boost 1.71 REQUIRED COMPONENTS
              system)
			  
IF(Boost_FOUND)
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
  LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

#Add libs to the build
add_subdirectory(lib)

#add the service source code
add_subdirectory(src)

#Set the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT service)
# TODO: Add tests and install targets if needed.
