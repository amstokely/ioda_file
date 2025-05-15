set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include("add_cpp_test")
set(ioda_file_SOURCES
        "ioda_obs_schema/ioda_obs_schema.cc"
)
list(TRANSFORM ioda_file_SOURCES PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")
set(ioda_file_INCLUDE_DIRECTORIES
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_BINARY_DIR}/generated"
)
set(ioda_file_LIBRARY_DEPENDENCIES
        yaml-cpp::yaml-cpp
)
add_library(ioda_file ${ioda_file_SOURCES})
target_include_directories(ioda_file
        PUBLIC
        ${ioda_file_INCLUDE_DIRECTORIES}
)
target_link_libraries(ioda_file
        PUBLIC
        ${ioda_file_LIBRARY_DEPENDENCIES}
)
add_subdirectory(ioda_obs_schema)
