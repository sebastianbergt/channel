add_executable(channel_example src/main.cpp)

find_package(Threads REQUIRED)

target_link_libraries(channel_example channel ${CMAKE_THREAD_LIBS_INIT})