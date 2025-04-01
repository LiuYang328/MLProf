#include "Dialect/profiling/profilingOps.h"
#include "Dialect/profiling/profilingDialect.h"

#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/IR/BuiltinTypeInterfaces.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/IntegerSet.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Support/LogicalResult.h"
#include "mlir/Transforms/InliningUtils.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/LogicalResult.h"
#include "llvm/Support/raw_ostream.h"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <optional>
#include <string>

using namespace mlir;

// 文件路径: lib/Dialect/Profiling/ProfilingOps.cpp

#include "Dialect/profiling/profilingOps.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/OpImplementation.h"

using namespace profiling;

// //===----------------------------------------------------------------------===//
// // profiling.yield 操作的验证和构建
// //===----------------------------------------------------------------------===//

// // 自动生成的构建方法（由 TableGen 生成）
// void YieldOp::build(OpBuilder &builder, OperationState &state, Value value) {
//   state.addOperands(value);
//   state.addTypes(value.getType());
// }

// //===----------------------------------------------------------------------===//
// // profiling.wrap 操作的验证和构建
// //===----------------------------------------------------------------------===//

// // 自定义构建方法（补充 TableGen 的自动生成）
// void WrapOp::build(OpBuilder &builder, OperationState &state, Type resultType,
//                    StringRef analysisType, Optional<StringRef> label) {
//   // 设置属性
//   state.addAttribute("analysis_type", builder.getStringAttr(analysisType));
//   if (label.has_value())
//     state.addAttribute("label", builder.getStringAttr(*label));

//   // 创建区域并添加一个空 Block
//   Region *bodyRegion = state.addRegion();
//   Block *block = new Block();
//   bodyRegion->push_back(block);

//   // 设置结果类型
//   state.addTypes(resultType);
// }

// // 验证逻辑：确保区域内有且仅有一个 Yield 操作作为终止
// LogicalResult WrapOp::verify() {
//   Region &body = getBody();

//   // 检查区域是否为空
//   if (body.empty())
//     return emitOpError("body region must not be empty");

//   Block &block = body.front();

//   // 检查 Block 是否有终止操作
//   if (block.empty())
//     return emitOpError("body block must have a terminator");

//   // 检查终止操作是否是 profiling.yield
//   Operation *terminator = block.getTerminator();
//   if (!isa<YieldOp>(terminator))
//     return emitOpError("body must end with profiling.yield");

//   // 检查 Yield 的操作数数量
//   YieldOp yield = cast<YieldOp>(terminator);
//   if (yield->getNumOperands() != 1)
//     return yield.emitOpError("must yield exactly one value");

//   // 检查 Yield 的操作数类型与 WrapOp 的结果类型是否一致
//   Type resultType = getResult().getType();
//   Type yieldType = yield.getOperand().getType();
//   if (resultType != yieldType)
//     return emitOpError("result type ")
//            << resultType << " does not match yield type " << yieldType;

//   return success();
// }

// 自动生成的类型推断接口（可选）
#define GET_OP_CLASSES
#include "profiling/profilingOps.cpp.inc" // 包含自动生成的 Op 类定义
