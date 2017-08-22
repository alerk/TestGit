cmake_minimum_required (VERSION 2.8)

project (EntranceTest)

set (CMAKE_CXX_STANDARD 14)

set (PROJECT_BINARY_DIR ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (PROJECT_REF_SRC ${PROJECT_SOURCE_DIR}/src)
set (PROJECT_TEST_CASE ${PROJECT_SOURCE_DIR}/test)

# Output paths
# set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
# set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
# set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

include_directories ("${PROJECT_INCLUDE_DIR}")

set (CXXTEST_SRC
    ${PROJECT_REF_SRC}/bug_fixing.cpp
    ${PROJECT_REF_SRC}/ptr_list_len.cpp
    ${PROJECT_REF_SRC}/deepest_pit.cpp
     )

# Build the implemented files
add_library (${PROJECT_NAME} ${CXXTEST_SRC})

# Unit tests
find_package (CxxTest)
if (CXXTEST_FOUND)
    include_directories (${CXXTEST_INCLUDE_DIR})
    enable_testing()

    CXXTEST_ADD_TEST (test/check_test1 test/check_test1.cc ${PROJECT_TEST_CASE}/check_test1.h)
    target_link_libraries (check_test1 EntranceTest)

    CXXTEST_ADD_TEST (test/check_test2 test/check_test2.cc ${PROJECT_TEST_CASE}/check_test2.h)
    target_link_libraries(check_test2 EntranceTest)

    CXXTEST_ADD_TEST (test/check_test3 test/check_test3.cc ${PROJECT_TEST_CASE}/check_test3.h)
    target_link_libraries(check_test3 EntranceTest)

endif ()
