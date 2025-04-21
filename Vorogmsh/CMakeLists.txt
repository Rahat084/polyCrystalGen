add_library( Vorogmsh vorogmsh.cpp)
add_library( adjacencyMatrix STATIC adjacencyMatrix.cpp)
target_link_libraries( Vorogmsh PRIVATE adjacencyMatrix)
target_include_directories(Vorogmsh PUBLIC "${CONDA_PREFIX}/include/voro++"
)
