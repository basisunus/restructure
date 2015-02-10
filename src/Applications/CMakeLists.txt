PROJECT(reference-cli CXX)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

include_directories(${CMAKE_BINARY_DIR}/include)

file(GLOB src *.c*)
file(GLOB hdr *.h)

add_executable(reference-cli ${hdr} ${src})

target_link_libraries(reference-cli reference)
