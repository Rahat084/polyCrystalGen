cmake_minimum_required( VERSION 3.10)
project( polyCrystalGen VERSION 1.1)
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

