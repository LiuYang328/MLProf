#include "mlir_profiler/Profiler.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/IR/Operation.h"
#include "mlir/Parser/Parser.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include <cstdio>
#include <iostream>
#include <string>

using namespace mlir;

std::string Profiler::instrument(const std::string &targetDialect) {
  // 解析 MLIR 源文件生成模块
  // mlir::OwningOpRef<mlir::ModuleOp> module = parseMLIRsrcfile(mlirFilePath);

  std::cout << "instrument" << std::endl;
  std::string mlirFilePath =
      "/root/myproject/MLIR-Profiler/MLProfiler/examples/matmul-test/matmul-with-time.mlir";

  auto moduleOp = mlir::parseSourceFile<mlir::ModuleOp>(mlirFilePath, &context);
  // 提取并执行对目标方言操作的处理逻辑

  mlir::OpBuilder builder(&context);

  
  moduleOp->walk([&](linalg::LinalgOp linalgOp) {
    // 遍历函数体中每个操作

    printf("Matched op: %s\n",
           linalgOp->getName().getStringRef().str().c_str());

    builder.setInsertionPoint(linalgOp);

    auto scopeOp = builder.create<profiling::ScopeOp>(linalgOp->getLoc());

    // Operation *opPtr = linalgOp.getOperation();
    // opPtr->remove(); // 从原 block 移除

    // Region &scopeRegion = scopeOp.getRegion();
    // Block *scopeBlock = builder.createBlock(&scopeRegion);

    // 将 linalg.matmul 操作插入到 scopeBlock 中
    // builder.setInsertionPointToEnd(scopeBlock);
    // builder.insert(opPtr);


  });

  moduleOp->dump();
  return "";
}



void _mlir_ciface_timingStart(uint64_t ptr) {
  Profiler::getTimeManager().timingStart(reinterpret_cast<TimeEvent *>(ptr));
}

void _mlir_ciface_timingEnd(uint64_t ptr) {
  Profiler::getTimeManager().timingEnd(reinterpret_cast<TimeEvent *>(ptr));
}


extern "C" void  _mlir_ciface_printtest() {
  std::cout << "print test" << std::endl;
}


std::unique_ptr<TimeManager> Profiler::timeManager = nullptr;
