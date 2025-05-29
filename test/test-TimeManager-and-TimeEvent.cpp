#include "Utils/compileUtils.h"
#include "Utils/logger.h"
#include "mlir/Debug/BreakpointManager.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/DialectRegistry.h"
#include "mlir/IR/Location.h"
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
#include <string>

#include "mlir/Pass/Pass.h"
#include "mlir_profiler/Profiler.h"
#include "mlir_profiler/TimeEvent.h"

// 封装 test-TimeManager-and-TimeEvent.cpp 中的测试逻辑
void testTimeManagerAndTimeEvent() {

  Profiler profiler("/home/liuyang/project/mlir-profiler/buddy-mlir/examples/profiler-lenet/log.mlir");

  TimeEvent event;

  TimeManager &m = profiler.getTimeManager();
  m.timingStart(&event);
  double timeevent = event.getStartTimestamp();

  std::cout << "start time: " << timeevent << std::endl;

  myutils::log(myutils::LogLevel::INFO, "finish Time test");
}

// 封装 test-Utils.cpp 中的测试逻辑
void testUtils() {

  myutils::log(myutils::LogLevel::INFO, "start myutils test");

  mlir::DialectRegistry registry;

  // 注册所有内置 dialect
  mlir::registerAllDialects(registry);

  // mlir::func::registerAllExtensions(registry);

  // 用注册表初始化 MLIRContext，所有注册的 dialect 都会被载入
  mlir::MLIRContext context(registry);
  context.allowUnregisteredDialects(true);

  // 读入文件
  auto src = parseSourceFile<mlir::ModuleOp>(
      "/root/myproject/MLIR-Profiler/MLProfiler/"
      "examples/matmul-test/matmul-with-time.mlir",
      &context);

  // src->dump();

  std::string name = "nihao";
  myutils::CompileUtils compileUtils(*src, name,
                                     myutils::CompileUtils::TARGET::MLIR);
}

int main(int argc, char **argv) {
  // 执行 TimeManager 和 TimeEvent 测试
  testTimeManagerAndTimeEvent();

  // 执行 Utils 测试
  testUtils();

  return 0;
}