cmake_minimum_required (VERSION 3.0)
set (CXX_STANDARD "c++17")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=${CXX_STANDARD}")

project (xlog)

set (xlog_VERSION_MAJOR 1)
set (xlog_VERSION_MINOR 0)

configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

find_package(fmt REQUIRED)

include_directories("/usr/local/include/")

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include/")

add_subdirectory(src/wrapper)


find_library(FMT_LIBRARY fmt HINTS /usr/local/lib)
set(EXTRA_LIBS ${EXTRA_LIBS} wrapper ${FMT_LIBRARY}) 

#####################################
add_executable(xlog-test src/xlog.cxx)
target_link_libraries(xlog-test  ${EXTRA_LIBS})

add_library(xlog SHARED src/xlog.cxx)
target_link_libraries(xlog  ${EXTRA_LIBS})

# add the install targets
install (TARGETS xlog DESTINATION lib)
install (DIRECTORY "${PROJECT_SOURCE_DIR}/include/xlog"        
         DESTINATION include)
