# Download Catch2

include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.3.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

# Build channel_tests

add_executable(channel_tests channel_tests.cpp)

find_package(Threads REQUIRED)

target_link_libraries(channel_tests PRIVATE channel Catch2::Catch2WithMain ${CMAKE_THREAD_LIBS_INIT})

enable_testing()

add_test(NAME channel_tests COMMAND channel_tests)
