#include "Dialect/profiling/profilingDialect.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Support/LogicalResult.h"
#include "Dialect/profiling/profilingOps.h"
#include "Dialect/profiling/profilingTypes.h"

#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/OpImplementation.h"
#include "mlir/Interfaces/FunctionImplementation.h"

#include "mlir/Dialect/Arith/IR/Arith.h"

using namespace mlir;
using namespace profiling;

#include "profiling/profilingDialect.cpp.inc"

void ProfilingDialect::initialize() {
  // registerTypes();

  addOperations<
#define GET_OP_LIST
#include "profiling/profilingOps.cpp.inc"
      >();
}