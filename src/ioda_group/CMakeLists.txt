
set(ioda_group_test_SOURCES
        "ioda_group.test.cpp"
)
set(ioda_group_test_INCLUDE_DIRECTORIES
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_BINARY_DIR}/generated"
)
set(ioda_group_test_LIBRARY_DEPENDENCIES
        ioda_file
        GTest::gtest_main
)
add_cpp_test(ioda_group_test
        "${ioda_group_test_SOURCES}"
        "${ioda_group_test_INCLUDE_DIRECTORIES}"
        "${ioda_group_test_LIBRARY_DEPENDENCIES}"
)
