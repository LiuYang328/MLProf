add_mlir_dialect_library(MLIRPROFILING
        profilingDialect.cpp
        profilingOps.cpp
        profilingTypes.cpp

        DEPENDS
        profilingDialectIncGen
        profilingOpsIncGen
        profilingTypesIncGen
        
        LINK_LIBS PUBLIC
        MLIRIR
        MLIRInferTypeOpInterface
)



