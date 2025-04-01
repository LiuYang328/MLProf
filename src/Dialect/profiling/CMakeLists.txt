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


include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/Dialect)
include_directories(${PROJECT_BINARY_DIR}/include)
include_directories(${PROJECT_BINARY_DIR}/include/Dialect)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include/Dialect)


