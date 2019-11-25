# CMakeList.txt : CMake project for Service, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


add_subdirectory(configuration)
add_subdirectory(platforms)

set(sources
	main.cpp
)

# Add source to this project's executable.
add_executable (service ${sources}  )
target_link_libraries (service configuration platform)


