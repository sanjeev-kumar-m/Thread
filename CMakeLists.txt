set(This Thread)

set(Sources
    include/Thread/Thread.hpp)

add_library(${This} INTERFACE)

target_include_directories(${This} INTERFACE include/)

add_subdirectory(test)
