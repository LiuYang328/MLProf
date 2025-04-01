#include "Dialect/profiling/profilingTypes.h"
#include "Dialect/profiling/profilingDialect.h"
#include "Dialect/profiling/profilingOps.h"

#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/Dialect/LLVMIR/LLVMTypes.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/DialectImplementation.h"
#include "mlir/IR/TypeSupport.h"

#include "mlir/IR/Builders.h"
#include "mlir/IR/OpImplementation.h"
#include "mlir/Interfaces/FunctionImplementation.h"

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/Hashing.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/ScopeExit.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/TypeSwitch.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/TypeSize.h"
#include <optional>

using namespace mlir;
using namespace profiling;

#define GET_TYPEDEF_CLASSES
#include "profiling/profilingTypes.cpp.inc"

// void MIXDialect::registerTypes() {
//     addTypes<
// #define GET_TYPEDEF_LIST
// #include "profiling/profilingTypes.cpp.inc"
//       >();
// }