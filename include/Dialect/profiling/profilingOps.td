// 定义 Profiling Dialect 的 Operations
#ifndef PROFILING_OPS_TD
#define PROFILING_OPS_TD

include "mlir/IR/OpBase.td"
include "mlir/IR/BuiltinAttributes.td"
include "mlir/Interfaces/FunctionInterfaces.td"
include "mlir/Interfaces/InferTypeOpInterface.td"
include "mlir/IR/SymbolInterfaces.td"
include "mlir/Interfaces/CallInterfaces.td"
include "mlir/Interfaces/CastInterfaces.td"
include "mlir/Interfaces/SideEffectInterfaces.td"
include "mlir/IR/CommonAttrConstraints.td"
include "mlir/IR/BuiltinTypes.td"
include "mlir/Dialect/Shape/IR/ShapeBase.td"

include "profilingTypes.td"
include "profilingDialect.td"



def ScopeOp : Profiling_Op<"scope",[Pure]> {
  let summary = "Scope operation to enclose a region for profiling.";
  let description = [{
    包裹一段被测试的代码段，会在后续 pass 中插入 profiling.start / profiling.end。
  }];

    // let arguments = (ins AnyType:$operation);
  let regions = (region AnyRegion:$region);
  // let results = (outs AnyType:$result);
  let hasCanonicalizer = 1;


}

//===----------------------------------------------------------------------===//
// StartOp 定义
//   - 记录性能起始时间
//   - 可选择性带有标签或标识
//===----------------------------------------------------------------------===//

def StartOp : Profiling_Op<"start", [Pure]> {
  let summary = "Start profiling time measurement.";
  let description = [{
    该操作表示开始记录性能计时，通常会插入一个获取当前时间的调用。
    该操作可以是异步的，用于开始性能测量。
  }];
  
  // 格式化输出时，不包含操作数与结果
  let assemblyFormat = "attr-dict";
}



#endif // PROFILING_OPS_TD