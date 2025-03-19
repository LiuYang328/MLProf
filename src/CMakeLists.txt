add_library(ProfilerRuntime SHARED TimeManager.cpp  Profiler.cpp TimeEvent.cpp ) 


target_include_directories(ProfilerRuntime PUBLIC ${PROJECT_SOURCE_DIR}/include)


target_link_libraries(ProfilerRuntime
    PUBLIC
    ${dialect_libs}
    ${conversion_libs}
    mlir_c_runner_utils
    mlir_runner_utils
)


