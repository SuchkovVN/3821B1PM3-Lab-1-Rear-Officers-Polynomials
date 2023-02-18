file(GLOB srcs "*.cpp")
file(GLOB hdrs "*.h")

add_library(ParseLib STATIC ${srcs} ${hdrs})