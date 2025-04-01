set(LLVM_TARGET_DEFINITIONS profilingDialect.td)
mlir_tablegen(profilingDialect.h.inc -gen-dialect-decls)
mlir_tablegen(profilingDialect.cpp.inc -gen-dialect-defs)
add_public_tablegen_target(profilingDialectIncGen)

set(LLVM_TARGET_DEFINITIONS profilingOps.td)
mlir_tablegen(profilingOps.h.inc -gen-op-decls)
mlir_tablegen(profilingOps.cpp.inc -gen-op-defs)
add_public_tablegen_target(profilingOpsIncGen)

set(LLVM_TARGET_DEFINITIONS profilingTypes.td)
mlir_tablegen(profilingTypes.h.inc -gen-typedef-decls -typedefs-dialect=profiling)
mlir_tablegen(profilingTypes.cpp.inc -gen-typedef-defs -typedefs-dialect=profiling)
add_public_tablegen_target(profilingTypesIncGen)



