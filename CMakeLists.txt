cmake_minimum_required( VERSION 3.10)
project( polyCrystalGen VERSION 1.1)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
add_subdirectory( Vorogmsh)
add_executable( polyCrystalGen polyCrystalGen.cpp )
#target_link_libraries( polyCrystalGen libvoro++)

# polyCrystalGen: Linking an external dynamic library
find_library(VORO_LIB Voro++
    HINTS "$ENV{CONDA_PREFIX}/lib" # Optional hint
)


if(VORO_LIB)
    target_link_libraries(polyCrystalGen PRIVATE ${VORO_LIB})
else()
    message(FATAL_ERROR "vorolib not found")
endif()

# Example: Linking a dynamic library built within the project
#add_library(my_dynamic_lib SHARED my_dynamic_lib.cpp)
#target_link_libraries(my_executable PRIVATE my_dynamic_lib)
target_link_libraries( polyCrystalGen PRIVATE Vorogmsh)

#Add include directories if needed
target_include_directories(polyCrystalGen PUBLIC 
    "${PROJECT_SOURCE_DIR}/Vorogmsh"
)


project( setPhysicalGroups VERSION 1.1)
add_executable( setPhysicalGroups setPhysicalGroups.cpp)
# setPhysicalGroup: Linking an external dynamic library gmsh
find_library(GMSH_LIB gmsh
    HINTS "$ENV{CONDA_PREFIX}/lib" # Optional hint
)
if(GMSH_LIB)
    target_link_libraries(setPhysicalGroups PRIVATE ${GMSH_LIB})
else()
    message(FATAL_ERROR "gmshlib not found")
endif()
target_include_directories( setPhysicalGroups PUBLIC 
    "$ENV{CONDA_PREFIX}/include")
