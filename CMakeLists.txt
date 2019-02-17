cmake_minimum_required (VERSION 3.0)
set (CXX_STANDARD "c++14")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=${CXX_STANDARD}")

project (xlog)

set (xlog_VERSION_MAJOR 1)
set (xlog_VERSION_MINOR 0)

configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include/")

add_subdirectory(src/wrapper)
set(EXTRA_LIBS ${EXTRA_LIBS} wrapper)

add_executable(xlog-test src/xlog.cxx)
target_link_libraries(xlog-test  ${EXTRA_LIBS})

add_library(xlog SHARED src/xlog.cxx)
target_link_libraries(xlog  ${EXTRA_LIBS})

# add the install targets
install (TARGETS xlog DESTINATION lib)
install (DIRECTORY "${PROJECT_SOURCE_DIR}/include/xlog"        
         DESTINATION include)
