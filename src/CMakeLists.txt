#-----------------------------------------------------------------------------
#
# FluoRender - A re-structured version.
# -- CMakeList
#
# Primary Author:        Yong Wan
# Contributing Authors:  
#                        Brig        Bagley  (brig@sci.utah.edu)
#
#-----------------------------------------------------------------------------
#-----------------------------------------------------------------------------
#
#  Copyright (C) 2015, Yong Wan
#  Scientific Computing and Imaging Institute
#  University of Utah
#
#
#  Permission is hereby  granted, free of charge, to any person obtaining a
#  copy of this software and associated documentation files (the "Software"),
#  to deal in the Software without restriction, including without limitation
#  the rights to  use, copy, modify,  merge, publish, distribute, sublicense,
#  and/or  sell  copies of  the Software, and  to permit persons to whom the
#  Software is  furnished to  do so,  subject  to  the following conditions:
#
#  The above copyright notice  and  this permission notice shall be included
#  in all copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING  BUT NOT  LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A  PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN  NO EVENT SHALL
#  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER  IN  AN  ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#  FROM, OUT  OF  OR IN  CONNECTION  WITH THE  SOFTWARE  OR  THE USE OR OTHER
#  DEALINGS IN THE SOFTWARE.
#-----------------------------------------------------------------------------

PROJECT(FluoRender)

# Global CMake options
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
OPTION(CMAKE_BUILD_TYPE Release)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
   add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# Build FluoRender
ADD_SUBDIRECTORY(lib/Reference)
ADD_SUBDIRECTORY(Applications)
########################################################################
# All of the testing and test framework options
INCLUDE(CTest)
if (BUILD_TESTING)
  ENABLE_TESTING()
  # Use gcov for code coverage (useful for seeing test completeness)
  OPTION(USE_GCOV "Enable code coverage for GNUCXX Platforms" OFF)
  if (USE_GCOV)
    if(CMAKE_COMPILER_IS_GNUCXX)
      INCLUDE(${PROJECT_SOURCE_DIR}/CodeCoverage.cmake)
      SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
      SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    endif()
  endif()
  ADD_SUBDIRECTORY(lib/gtest)
  ADD_SUBDIRECTORY(test)
endif()
