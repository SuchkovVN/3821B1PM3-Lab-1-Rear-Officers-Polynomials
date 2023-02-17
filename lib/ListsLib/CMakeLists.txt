file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")
add_library(ListsLib STATIC ${srcs} ${hdrs})