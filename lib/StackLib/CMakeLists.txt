file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")
add_library(StackLib STATIC ${srcs} ${hdrs})
