file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")
add_library(AEL STATIC ${srcs} ${hdrs})
