set(This ThreadTest)
set(Sources
  src/ThreadTest.cpp)

add_executable(${This} ${Sources})

target_link_libraries(${This}
  pthread Thread)   