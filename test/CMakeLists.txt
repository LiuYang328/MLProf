include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/Dialect)
include_directories(${PROJECT_BINARY_DIR}/include)
include_directories(${PROJECT_BINARY_DIR}/include/Dialect)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include/Dialect)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)



add_executable(test "test-TimeManager-and-TimeEvent.cpp")



target_include_directories(test 
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/include/Dialect

    )
target_link_libraries(test
    PUBLIC
    compileUtils
    ProfilerRuntime
    mlir_runner_utils
    mlir_c_runner_utils
    ${dialect_libs}
    ${conversion_libs}
    
)
