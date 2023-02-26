project(lib)
#includes
include_directories(MML)
include_directories(ListsLib)
include_directories(ArithmExpressionsLib)
include_directories(StackLib)
#adding libs

#MML (Maksim's Map Library)
add_subdirectory(MML)
#AEL
add_subdirectory(ArithmExpressionsLib)
#Lists Lib 
add_subdirectory(ListsLib)
#StackLib
add_subdirectory(StackLib)


