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



int main(int argc, char **argv) {


  Profiler profiler;

  TimeEvent event;

  TimeManager &m = profiler.getTimeManager();
  m.timingStart(&event);
  double timeevent =  event.getStartTimestamp();

  std::cout << "start time: " << timeevent << std::endl;

  return 0;
}