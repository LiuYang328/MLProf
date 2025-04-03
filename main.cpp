// #include "mlir/IR/AsmState.h"
#include "Dialect/profiling/profilingDialect.h"
#include "Dialect/profiling/profilingOps.h"
#include "mlir/Debug/BreakpointManager.h"
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
#include "mlir_profiler/Profiler.h"
#include "llvm/Support/Process.h"
#include "llvm/Support/raw_ostream.h"
#include <cstdio>
#include <iostream>

#include "mlir/Pass/Pass.h"
#include "mlir_profiler/Profiler.h"
#include "mlir_profiler/TimeEvent.h"

using namespace mlir;

void visitOperation(Operation *op) {
  // 打印当前操作的信息
  std::cout << "visiting op: '" << op->getName().getStringRef().str()
            << "' with " << op->getNumOperands() << " operands and "
            << op->getNumResults() << " results\n";

  // 递归遍历所有子操作（通过regions和blocks）
  for (Region &region : op->getRegions()) {
    for (Block &block : region) {
      for (Operation &subOp : block) {
        visitOperation(&subOp); // 递归处理每个子操作
      }
    }
  }
}

void insertSurroundingOps(Operation *rootOp) {
  // 后序遍历所有子操作，避免修改父操作影响迭代器
  rootOp->walk([&](Operation *currentOp) {
    // 跳过顶层 module 操作（可选）
    if (currentOp->getName().getStringRef() == "builtin.module")
      return;

    OpBuilder builder(currentOp);

    // 在目标操作前插入 PRE_OP
    builder.setInsertionPoint(currentOp);
    OperationState preState(currentOp->getLoc(), "your_dialect.pre_op");
    Operation *preOp = builder.create(preState);

    // 在目标操作后插入 POST_OP
    builder.setInsertionPointAfter(currentOp);
    OperationState postState(currentOp->getLoc(), "your_dialect.post_op");
    Operation *postOp = builder.create(postState);

    // （可选）建立操作间的数据流关系
    // postOp->setOperand(0, currentOp->getResult(0));
  });
}

int main(int argc, char **argv) {

  mlir::DialectRegistry registry;

  // 注册所有内置 dialect
  mlir::registerAllDialects(registry);

  // mlir::func::registerAllExtensions(registry);

  // 用注册表初始化 MLIRContext，所有注册的 dialect 都会被载入
  mlir::MLIRContext context(registry);
  context.allowUnregisteredDialects(true);

  // 读入文件
  // auto src = parseSourceFile<ModuleOp>(argv[1], &ctx);

  // src->dump();

  // 在main中调用
  // Operation *root = src->getOperation(); // 获取顶层module操作
  // visitOperation(root);

  // insertSurroundingOps(root);

  Profiler profiler;

  TimeEvent event;

  TimeManager &m = profiler.getTimeManager();
  m.timingStart(&event);
  double timeevent =  event.getStartTimestamp();

  std::cout << "start time: " << timeevent << std::endl;


  // mlir::PassManager pm(moduleOp.get()->getName());
  // // if (mlir::failed(mlir::applyPassManagerCLOptions(pm)))
  // //   return 4;
  // pm.addNestedPass<func::FuncOp>(mlir::createCanonicalizerPass());
  // if (mlir::failed(pm.run(*moduleOp)))
  //   std::cout << "Failed to run pass" << std::endl;
  // else
  //   std::cout << "Pass ran successfully" << std::endl;


  // if (mlir::failed(moduleOp->verify()))
  //  std::cout<<"falied"<<std::endl;
  
  // moduleOp->dump();

  return 0;
}