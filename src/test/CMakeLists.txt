########################################################################
# Tests for FluoRender
include_directories(${FluoRender_SOURCE_DIR}/lib/Reference)
include_directories(${FluoRender_SOURCE_DIR}/lib/gtest)
include_directories(${FluoRender_SOURCE_DIR}/lib/gtest/include)
#reference library tests
cxx_test(object_unit_tests gtest_main)
target_link_libraries(object_unit_tests reference)
