# Test Common
add_executable(test_common
    test_types.cpp
    ../src/common/types.cpp
)

target_include_directories(test_common PRIVATE
    ../include
)

target_link_libraries(test_common
    gtest
    gtest_main
)

# Test Subsets
add_executable(test_subsets
    test_subsets.cpp
    ../src/model/subsets.cpp
)

target_include_directories(test_subsets PRIVATE
    ../include
)

target_link_libraries(test_subsets
    gtest
    gtest_main
)

add_test(NAME TestCommon COMMAND test_common)
add_test(NAME TestSubsets COMMAND test_subsets)
