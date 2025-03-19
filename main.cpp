// #include "mlir/IR/AsmState.h"
#include "ml_profiler/Profiler.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/DialectRegistry.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Operation.h"
#include "mlir/InitAllDialects.h" // 包含所有内置 dialect 的注册函数
#include "mlir/Parser/Parser.h"
#include "mlir/Support/FileUtilities.h"
#include "llvm/Support/Process.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>

#include "ml_profiler/Profiler.h"
#include "mlir/Pass/Pass.h"

using namespace mlir;

int main(int argc, char **argv) {

  mlir::DialectRegistry registry;

  // 注册所有内置 dialect
  mlir::registerAllDialects(registry);

  // 用注册表初始化 MLIRContext，所有注册的 dialect 都会被载入
  mlir::MLIRContext ctx(registry);

  // 读入文件
  auto src = parseSourceFile<ModuleOp>(argv[1], &ctx);
  // 输出dialect，也可以输出到 llvm::errs(), llvm::dbgs()
  // src->print(llvm::outs());
  // // 简单的输出，在 debug 的时候常用
  // src->dump();
  Operation *op = src->getOperation();
  std::cout << "Operation name: " << op->getName().getStringRef().str()
            << std::endl;

            std::cout << "visiting op: '" << op->getName().getStringRef().str() << "' with "
                << op->getNumOperands() << " operands and "
                << op->getNumResults() << " results\n";
  // Print the operation attributes
  if (!op->getAttrs().empty()) {
    std::cout << op->getAttrs().size() << " attributes:\n";
    for (NamedAttribute attr : op->getAttrs())
      std::cout << " - '" << attr.getName().str()<< "' : '"<< "'\n";
  }
  // Profiler profiler;

  // profiler.instrument("linalg");

  // 初始化 MLIR 环境。

  // 构造并执行 Pass 管线。

  // 与性能计数（硬件及软件）的上层模块解耦。

  return 0;
}