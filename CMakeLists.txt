cmake_minimum_required(VERSION 3.25)

set(project_name "Benchmark Containers")
project("${project_name}")

# Set search dir for includes and find packages.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/Modules")

# Set the default C++ standard.
set(CMAKE_CXX_STANDARD 23)

# If compiling with Clang in Linux, make sure to use libc++.
if( CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND LINUX)
  # Add c++ compiler flags here:
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++" )         # Add LLVM's libc++ standard library.
  #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexperimental-library")  # Need exp for jthread and stop_token.
  # Linker flags here:
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
endif()

# Attempt to folderize things
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Add third party stuff here
add_subdirectory(third_party)


add_subdirectory(deque)
