file(GLOB headers "*.h")
file(GLOB sources "*.cpp")

list(APPEND sources ${headers})

add_library(configuration STATIC ${sources})
