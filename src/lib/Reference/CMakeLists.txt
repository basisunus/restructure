PROJECT(referenceLib)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

#project version
SET(${PROJECT_NAME}_MAJOR_VERSION 1)
SET(${PROJECT_NAME}_MAJOR_VERSION 0)

file(GLOB src *.c*)
file(GLOB hdr *.h)

SET(Reference_API_HEADER_FILES ${hdr})

SET(Reference_INSTALLED_HEADER_FILES)
foreach(file ${Reference_API_HEADER_FILES})
   get_filename_component(file_no_path "${file}" NAME)
   configure_file("${file}"
      "${CMAKE_BINARY_DIR}/include/Reference/${file_no_path}" COPYONLY IMMEDIATE)
   SET(Reference_INSTALLED_HEADER_FILES
      ${Reference_INSTALLED_HEADER_FILES}
      "${CMAKE_BINARY_DIR}/include/Reference/${file_no_path}")
endforeach()

add_library(reference STATIC ${hdr} ${src})
