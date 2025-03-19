cmake_minimum_required(VERSION 3.10)

project(ml-profiler)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # 生成 compile_commands.json 便于代码高亮
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)



#-------------------------------------------------------------------------------
# MLIR/LLVM Configuration
#-------------------------------------------------------------------------------
set(MLIR_DIR /root/third-lib/llvm-project/build-19.1.7/lib/cmake/mlir)
set(LLVM_DIR /root/third-lib/llvm-project/build-19.1.7/lib/cmake/llvm)

find_package(MLIR REQUIRED CONFIG)

message(STATUS "Using MLIRConfig.cmake in: ${MLIR_DIR}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

list(APPEND CMAKE_MODULE_PATH "${MLIR_CMAKE_DIR}")
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
message("mlir cmake dir: ${MLIR_CMAKE_DIR}")
message("llvm cmake dir: ${LLVM_CMAKE_DIR}")
include(TableGen)
include(AddLLVM)
include(AddMLIR)
include(HandleLLVMOptions)

# Add MLIR and LLVM headers to the include path
include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${MLIR_INCLUDE_DIRS})


add_executable(profiler-main main.cpp)


# find MLIR libraries
get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)

add_subdirectory(examples)
add_subdirectory(src)


target_include_directories(profiler-main PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(profiler-main
    PUBLIC
    ProfilerRuntime
    mlir_runner_utils
    mlir_c_runner_utils
    ${dialect_libs}
    ${conversion_libs}
)