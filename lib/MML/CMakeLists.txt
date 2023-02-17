file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")
add_library(MML STATIC ${srcs} ${hdrs})