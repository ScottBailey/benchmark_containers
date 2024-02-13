set(target_name deque)

file(GLOB src_cpp *.cpp)


add_executable(${target_name} ${src_cpp} ${src_h})

target_include_directories(${target_name} PRIVATE . )

target_link_libraries(${target_name}
  benchmark
  Boost::container
)
