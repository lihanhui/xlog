add_library(wrapper wrapper.cxx)

install (TARGETS wrapper DESTINATION lib
         EXPORT xlog-targets )
