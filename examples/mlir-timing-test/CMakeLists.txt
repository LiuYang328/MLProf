add_executable(mlir-timing-test mlir-timing-test.cpp)


target_link_libraries(mlir-timing-test
    PUBLIC
    MLIRSupport
    LLVMSupport
    ${dialect_libs}
    ${conversion_libs}
)
