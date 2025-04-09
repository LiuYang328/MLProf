llvm_map_components_to_libnames(llvm_libs Support)
get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)


add_library(profilerlogger
    STATIC
    logger.cpp
)


add_library(compileUtils
    STATIC
    compileUtils.cpp
)


target_link_libraries(compileUtils
    PRIVATE
    LLVMSupport
    MLIRToLLVMIRTranslationRegistration
    MLIRFromLLVMIRTranslationRegistration
    LLVMX86Info
    # LLVMX86TargetMCA
    LLVMX86Disassembler
    LLVMX86Desc
    LLVMX86CodeGen
    LLVMX86AsmParser
    MLIRTargetCpp
    MLIRFuncAllExtensions
    MLIRSPIRVTranslateRegistration
    MLIRLLVMIRToLLVMTranslation
    lldELF
    lldCommon
    ${dialect_libs}
    ${conversion_libs}
    profilerlogger
)