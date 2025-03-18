#include "ml_profiler/Profiler.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/IR/Operation.h"
#include "mlir/Parser/Parser.h"
#include <cstdio>
#include <iostream>
#include <string>

std::string Profiler::instrument(const std::string &targetDialect) {
  // 解析 MLIR 源文件生成模块
  // mlir::OwningOpRef<mlir::ModuleOp> module = parseMLIRsrcfile(mlirFilePath);

  std::cout << "instrument" << std::endl;
  // auto moduleOp = module.get();
  // auto src = parseSourceFile<ModuleOp>(argv[1], &ctx);
  std::string mlirFilePath =
      "/root/myproject/MLIR-Profiler/MLProfiler/examples/matmul-vs-matvec.mlir";

  auto moduleOp = mlir::parseSourceFile<mlir::ModuleOp>(mlirFilePath, &context);
  // 提取并执行对目标方言操作的处理逻辑

  mlir::OpBuilder builder(&context);

  std::cout << "start walk" << std::endl;

  // 遍历模块中的所有函数
  moduleOp->walk([&](mlir::Operation *op) {
    // 遍历函数体中每个操作

    printf("Matched op: %s\n", op->getName().getStringRef().str().c_str());


    builder.setInsertionPoint(op);
    auto constantOp = builder.create<mlir::arith::ConstantOp>(
      op->getLoc(), builder.getI64IntegerAttr(42));

  });

  // // 输出文件路径构造
  // std::string fileName = mlirFilePath.stem();
  // std::filesystem::path parent_directory = mlirFilePath.parent_path();
  // std::filesystem::path new_file_path =
  //     parent_directory / (fileName + "_instrumented.mlir");

  // // 写入输出文件
  // std::error_code errorCode;
  // llvm::ToolOutputFile outputFile(new_file_path.string(), errorCode,
  //                                 llvm::sys::fs::OpenFlags(1)); // OF_Text

  // if (errorCode) {
  //   llvm::errs() << "Error opening output file: " << errorCode.message()
  //                << "\n";
  // }

  // moduleOp->print(outputFile.os());
  // outputFile.keep();
  // return new_file_path.string();
  moduleOp->dump();
  return "";
}
