# third_party/CMakeLists.txt

# Use CMake's FetchContent/MakeAvailable to download and compile dependencies via the CPM tool.

# This page will help you determine where source code archives live at github:
#   https://docs.github.com/en/repositories/working-with-files/using-files/downloading-source-code-archives
#


# Default FetchContent to Verbose. But don't override a user's explicit setting.
if(NOT FETCHCONTENT_QUIET)
  set(FETCHCONTENT_QUIET Off)
endif()

# Make sure to cache third party downloads, but don't override a user's explicit setting.
if(MSVC AND NOT CPM_SOURCE_CACHE)
  set(CPM_SOURCE_CACHE "C:/cpm_cache/")
endif()

# Set the name of the base folder. In IDEs such as MS Visual Stuido,
# this will do a nice job "containerizing" the files into folders.
set(BASE_FOLDER "3rdparty")


# Download and include `CPM.cmake`:
file(
  DOWNLOAD      https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.38.7/CPM.cmake ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
  EXPECTED_HASH SHA256=83e5eb71b2bbb8b1f2ad38f1950287a057624e385c238f6087f94cdfc44af9c5
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)


# Make sure we have a patch utility.
if(WIN32)
  # TBD: fix assumptions in this search.
  find_package(Git QUIET)
  cmake_path(GET GIT_EXECUTABLE PARENT_PATH extra_search_path)
  cmake_path(GET extra_search_path PARENT_PATH extra_search_path)
  set(extra_search_path "${extra_search_path}/usr/bin")
  find_program(PATCH_EXE patch HINTS ${extra_search_path})
else()
  find_program(PATCH_EXE patch)
endif()
if(NOT PATCH_EXE)
  message(FATAL_ERROR "Couldn't find `patch` executable.")
endif()

# Get google's benchmarking tool
set(CMAKE_FOLDER "${BASE_FOLDER}/benchmark")
CPMAddPackage(
  NAME     benchmark
  URL      https://github.com/google/benchmark/archive/refs/tags/v1.8.3.tar.gz
  URL_HASH SHA256=6bc180a57d23d4d9515519f92b0c83d61b05b5bab188961f36ac7b06b0d9e9ce
  SYSTEM   True
  OPTIONS
    "BENCHMARK_ENABLE_INSTALL Off"
    "BENCHMARK_ENABLE_TESTING Off"
    "BENCHMARK_INSTALL_DOCS Off"
    "BENCHMARK_ENABLE_GTEST_TESTS Off"
)


# Boost libraries
#  This speaks for itself.
set(CMAKE_FOLDER "${BASE_FOLDER}/Boost")
CPMAddPackage(
  NAME     Boost
  URL      https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.xz
  URL_HASH SHA256=2e64e5d79a738d0fa6fb546c6e5c2bd28f88d268a2a080546f74e5ff98f29d0e
  SYSTEM   True
  OPTIONS
    "BOOST_ENABLE_CMAKE ON"
    "BUILD_SHARED_LIBS Off"
    "BOOST_INCLUDE_LIBRARIES container"
)



#
set(CMAKE_FOLDER "${BASE_FOLDER}")
