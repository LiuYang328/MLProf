add_library(ProfilerRuntime SHARED 
    TimeManager.cpp  
    Profiler.cpp 
    TimeEvent.cpp 
) 


target_include_directories(ProfilerRuntime
    INTERFACE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/mlir_profiler
    ${CMAKE_CURRENT_BINARY_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/include/Dialect
)


target_link_libraries(ProfilerRuntime
    PUBLIC
    MLIRPROFILING
    mlir_c_runner_utils
    mlir_runner_utils
    profilingpass

    ${dialect_libs}
    ${conversion_libs}
)