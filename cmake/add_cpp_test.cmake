function(add_cpp_test name sources include_directories library_dependencies)
    add_executable(${name} ${sources})
    target_include_directories(${name} PRIVATE ${include_directories})
    target_link_libraries(${name} PRIVATE ${library_dependencies})
    add_test(
            NAME ${name}
            COMMAND ${name} --gtest_filter=*
    )
endfunction()