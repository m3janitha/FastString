include_directories(${PROJECT_SOURCE_DIR}/include)

file( GLOB TEST_SOURCES *.cpp)
foreach( test_sourcefile ${TEST_SOURCES} )
    get_filename_component(EXECUTABLE_NAME ${test_sourcefile} NAME_WE)
    string( REPLACE ".cpp" "" ${EXECUTABLE_NAME} ${test_sourcefile} )
    #add_executable( ${test_name} ${test_sourcefile} )
    message("add_executable ${EXECUTABLE_NAME} ${test_sourcefile}") 
    add_executable(${EXECUTABLE_NAME} ${test_sourcefile})    
    target_link_libraries(${EXECUTABLE_NAME} GTest::gtest GTest::gtest_main)
    add_test(NAME ${EXECUTABLE_NAME} COMMAND ${EXECUTABLE_NAME})
endforeach( test_sourcefile ${TEST_SOURCES} )

