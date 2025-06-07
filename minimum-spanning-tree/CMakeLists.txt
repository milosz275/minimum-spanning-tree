# CMakeList.txt : CMake project for minimum-spanning-tree, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (minimum-spanning-tree
    "main.cpp"
    "src/common/types.cpp"
    "src/geometry/visualization.cpp"
    "src/model/solver.cpp"
    "src/model/subsets.cpp"
)

target_include_directories(minimum-spanning-tree PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(minimum-spanning-tree
    cplex${CPLEX_VERSION}.lib
    concert.lib
    ilocplex.lib
    CDT
)

if (CMAKE_VERSION VERSION_GREATER 3.15)
  set_property(TARGET minimum-spanning-tree PROPERTY CXX_STANDARD 20)
endif()

# GoogleTest via FetchContent
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# For Windows: prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
if(NOT googletest_POPULATED)
  FetchContent_MakeAvailable(googletest)
endif()

# Add the tests directory
add_subdirectory(tests)
