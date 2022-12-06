#
# enumerator
# 
# Written by Edward H. Trager 
# <ed.trager@gmail.com>
# <ehtrager@med.umich.edu>
#
# (c) 2022 by the Regents of the University of Michigan
# 
#     Released under the GNU GPL
#     
PROJECT(ENUMERATOR)
CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
MARK_AS_ADVANCED(CMAKE_BACKWARDS_COMPATIBILITY)

if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

#
# The enumerator version number:
# 
SET(ENUMERATOR_VERSION_MAJOR 1)
SET(ENUMERATOR_VERSION_MINOR 0)
SET(ENUMERATOR_VERSION "${ENUMERATOR_VERSION_MAJOR}.${ENUMERATOR_VERSION_MINOR}")

#
# Enable CTest
#
ENABLE_TESTING()

#
# Recurse subdirectories:
#
ADD_SUBDIRECTORY(src)

INCLUDE_DIRECTORIES(${ENUMERATOR_SOURCE_DIR} ${ENUMERATOR_BINARY_DIR})


#
# Put compiled libraries and executables in specified directories:
#
SET( LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/libs )
SET( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )


