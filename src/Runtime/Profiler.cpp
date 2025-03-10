#include "Profiler.h"

std::unique_ptr<TimeManager> Profiler::timeManager = nullptr;

std::string Profiler::instrument(const std::string &targetDialect) {
  mlir::OwningOpRef<mlir::ModuleOp> module = parseMLIRsrcfile(mlirFilePath);

  /* pass */

  mlir::OpBuilder builder(&context);
  auto moduleOp = module.get();
  // Insert the rtclock function declaration at the beginning of the module
  builder.setInsertionPointToStart(moduleOp.getBody());

  auto i64Type = builder.getIntegerType(64);
  auto rtFuncType = builder.getFunctionType({i64Type}, {});

  // declare func.func private @timingStart()
  auto timingStartFunc = builder.create<mlir::func::FuncOp>(
      moduleOp.getLoc(), "timingStart", rtFuncType);
  timingStartFunc.setPrivate();

  // declare func.func private @timingEnd()
  auto timingEndFunc = builder.create<mlir::func::FuncOp>(
      moduleOp.getLoc(), "timingEnd", rtFuncType);
  timingEndFunc.setPrivate();

  TimeManager &timeManager = getTimeManager();

  // do loop
  moduleOp.walk([&](mlir::func::FuncOp funcOp) {
    // llvm::outs() << "Function name: " << funcOp.getName() << "\n";
    if (funcOp == timingStartFunc || funcOp == timingEndFunc) {
      // llvm::outs() << "return\n";
      return;
    }

    // match all Ops of xxx dialect
    for (mlir::Operation &op : funcOp.getBody().front().getOperations()) {
      // llvm::outs << op->getName().getStringRef() << "\n";
      // get the dialect name of the Op
      mlir::StringRef opDialectName = op.getName().getDialectNamespace();

      // check dialect name
      if (opDialectName == targetDialect) {

        // add TimeEvent and instrumentation
        TimeEvent *event = new TimeEvent(&op);
        timeManager.addEvent(event);

        // add call start before target op
        builder.setInsertionPoint(&op);
        auto constantOp = builder.create<mlir::arith::ConstantOp>(
            op.getLoc(), i64Type,
            builder.getIntegerAttr(i64Type, uint64_t(event)));

        builder.create<mlir::func::CallOp>(op.getLoc(), timingStartFunc,
                                           mlir::ValueRange{constantOp});

        // add call end after target op
        builder.setInsertionPointAfter(&op);
        builder.create<mlir::func::CallOp>(op.getLoc(), timingEndFunc,
                                           mlir::ValueRange{constantOp});
      }
    }
  });
  

  // output file 
  // std::filesystem::path filePath = inputFilePath;
  std::string fileName = mlirFilePath.stem();
  std::filesystem::path parent_directory = mlirFilePath.parent_path();
  std::filesystem::path new_file_path =
      parent_directory / (fileName + "_instrumented.mlir");
  std::error_code errorCode;
  llvm::ToolOutputFile outputFile(new_file_path.string(), errorCode,
                                  llvm::sys::fs::OpenFlags(1)); // OF_Text


  if (errorCode) {
    llvm::errs() << "Error opening output file: " << errorCode.message()
                 << "\n";
  }

  moduleOp->print(outputFile.os());
  outputFile.keep();
  return new_file_path.string();
}

void Profiler::compile(const std::string &target) {
  std::thread t(&buddy::runtime::Profiler::makeTarget, this, target);
  t.join();
}

void Profiler::makeTarget(const std::string &target) {
  std::string targetFullName = "profiling-" + target;
  std::string makeCommand = "make " + targetFullName;

  int result = std::system(makeCommand.c_str());

  if (result == 0) {
    std::cout << "Shared " + target + " library compiled successfully."
              << std::endl;
  } else {
    std::cerr << "Failed command: `" + makeCommand +
                     "` to compile shared library."
              << std::endl;
  }
}

mlir::OwningOpRef<mlir::ModuleOp>
Profiler::parseMLIRsrcfile(std::string mlirFilePath) {
  this->mlirFilePath = mlirFilePath;
  // use  SourceMgr of LLVM to manage the files
  llvm::SourceMgr sourceMgr;
  auto fileOrErr = llvm::MemoryBuffer::getFileOrSTDIN(mlirFilePath);
  if (std::error_code ec = fileOrErr.getError()) {
    llvm::errs() << "Error reading file: " << ec.message() << "\n";
    return nullptr;
  }

  sourceMgr.AddNewSourceBuffer(std::move(*fileOrErr), llvm::SMLoc());

  mlir::ParserConfig config(&context);

  // Parse the ModuleOp in the file
  mlir::OwningOpRef<mlir::ModuleOp> module =
      mlir::parseSourceFile<mlir::ModuleOp>(sourceMgr, config);

  if (!module) {
    llvm::errs() << "Failed to parse MLIR file!\n";
    return nullptr;
  }
  return module;
}

