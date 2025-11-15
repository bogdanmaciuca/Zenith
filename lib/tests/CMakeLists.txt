include(CTest)
enable_testing()

set(TESTS_DIR unit)

add_subdirectory(mctest)

function(zn_add_test TEST_NAME)
    add_executable(${TEST_NAME} ${TESTS_DIR}/${TEST_NAME}.cpp)
    target_link_libraries(${TEST_NAME} PRIVATE zenithlib mctest)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

zn_add_test(lexer)

