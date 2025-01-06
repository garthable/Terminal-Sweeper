add_library(mineSweeper STATIC src/mineSweeper.cpp)
target_include_directories(mineSweeper PUBLIC include)

target_link_libraries(mineSweeper PUBLIC sVector)