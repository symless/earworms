
set (headers )

set(source )

add_subdirectory(common)

IF(Boost_FOUND)
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
  LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

list(APPEND sources ${headers})
add_library(platform STATIC ${sources} common/songs.h common/songs.cpp)