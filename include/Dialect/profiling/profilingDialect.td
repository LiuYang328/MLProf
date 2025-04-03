// 定义 Profiling Dialect
#ifndef PROFILING_DIALECT
#define PROFILING_DIALECT

include "mlir/IR/OpBase.td"
include "mlir/IR/DialectBase.td"


def Profiling_Dialect : Dialect {
  let name = "profiling";
  let summary = "Dialect for inserting performance profiling instrumentation";
  let cppNamespace = "::profiling";



}

//===----------------------------------------------------------------------===//
// Operation 基类 (可选)
// 如果想让所有 profiling 下的操作都共用一些共性 Trait，可以定义一个
// Profiling_Op<> 基类，再让具体的 Op 继承。这里仅示例。
//===----------------------------------------------------------------------===//
class Profiling_Op<string mnemonic, list<Trait> traits = []> :
    Op<Profiling_Dialect, mnemonic, traits>;



#endif // PROFILING_DIALECT