cmake_minimum_required (VERSION 3.0)

set (CXX_STANDARD "c++17")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=${CXX_STANDARD}")

project (xlog VERSION 1.0.0)

configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include/")
include_directories("/usr/local/include")

find_library(FMT_LIBRARY fmt HINTS /usr/local/lib)
set(EXTRA_LIBS ${EXTRA_LIBS} wrapper ${FMT_LIBRARY}) 
 
add_subdirectory(src/wrapper)
set(EXTRA_LIBS ${EXTRA_LIBS} wrapper)

#include(ExternalProject)
#ExternalProject_Add (
#      fmt
#      GIT_REPOSITORY "https://github.com/fmtlib/fmt.git"
#      GIT_TAG "5.3.0"
#      UPDATE_COMMAND ""
#      INSTALL_COMMAND "" )


#####################################
add_executable(xlog-test src/xlog.cxx)
target_link_libraries(xlog-test  ${EXTRA_LIBS})

add_library(xlog SHARED src/xlog.cxx)
set_target_properties(xlog PROPERTIES VERSION 1.0 SOVERION 1)
target_link_libraries(xlog  ${EXTRA_LIBS})

# add the install targets
install (TARGETS xlog DESTINATION lib
         EXPORT xlog-targets )
install (DIRECTORY "${PROJECT_SOURCE_DIR}/include/xlog"
         DESTINATION include)
install (EXPORT xlog-targets
         DESTINATION lib/cmake/xlog)

export (TARGETS xlog wrapper FILE xlog-targets.cmake)
configure_file ( "${PROJECT_SOURCE_DIR}/pkg/xlog-config.cmake.in"
                 "${PROJECT_BINARY_DIR}/xlog-config.cmake" @ONLY)
                 
configure_file ( "${PROJECT_SOURCE_DIR}/pkg/xlog-config-version.cmake.in"
                 "${PROJECT_BINARY_DIR}/xlog-config-version.cmake" @ONLY)
                 
install (FILES 
        "${PROJECT_BINARY_DIR}/xlog-config.cmake"
        "${PROJECT_BINARY_DIR}/xlog-config-version.cmake"
        DESTINATION lib/cmake/xlog)
