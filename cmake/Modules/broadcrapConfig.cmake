INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_BROADCRAP broadcrap)

FIND_PATH(
    BROADCRAP_INCLUDE_DIRS
    NAMES broadcrap/api.h
    HINTS $ENV{BROADCRAP_DIR}/include
        ${PC_BROADCRAP_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    BROADCRAP_LIBRARIES
    NAMES gnuradio-broadcrap
    HINTS $ENV{BROADCRAP_DIR}/lib
        ${PC_BROADCRAP_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(BROADCRAP DEFAULT_MSG BROADCRAP_LIBRARIES BROADCRAP_INCLUDE_DIRS)
MARK_AS_ADVANCED(BROADCRAP_LIBRARIES BROADCRAP_INCLUDE_DIRS)

