#
# ENUMERATOR SRC CMAKE FILE
#
# (c) 2022 by the Regents of the University of Michigan
# 
#     Released under the GNU GPL
#
#SET(CMAKE_BUILD_TYPE Debug)

SET( SOURCES 

  CLP.cpp
  Message.cpp
  utilities.cpp 
  VT100.cpp 
  Warning.cpp 
 
  # this is main.cpp: 
  main.cpp

)

#
# Where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked:
# 
SET(CMAKE_MODULE_PATH "${ENUMERATOR_SOURCE_DIR}/cmake/modules")

#
# Include FindPkgConfig.cmake
#
INCLUDE( UsePkgConfig )

SET( PACKAGE enumerator)
#SET( LOCALEDIR ${CMAKE_INSTALL_PREFIX}/share/locale )
#CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake ${CHECK_CSV_BINARY_DIR}/config.h)
INCLUDE_DIRECTORIES( ${ENUMERATOR_BINARY_DIR} )

#
# Executables:
#
ADD_EXECUTABLE(enumerator ${SOURCES} )
TARGET_COMPILE_FEATURES(enumerator PUBLIC cxx_std_17)

#
# Link target:
#
TARGET_LINK_LIBRARIES(enumerator 
	${requiredLibs} 
	${optionalLibs}
	stdc++	
)

#
# Installation directory:
#
MESSAGE(STATUS "=== NOTA BENE: === enumerator will be installed in ${CMAKE_INSTALL_PREFIX}")

#
# Installable items:
#
INSTALL_TARGETS( /bin enumerator )

