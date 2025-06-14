#ifndef ML_PROFILER_PROFILER_H
#define ML_PROFILER_PROFILER_H

#include "mlir/Dialect/Bufferization/Transforms/Passes.h"
#include "mlir/Dialect/Linalg/Passes.h"
#include "mlir/IR/Dialect.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/InitAllDialects.h"
#include "mlir/InitAllExtensions.h"
#include "mlir/InitAllPasses.h"
#include "mlir/Parser/Parser.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Support/FileUtilities.h"
#include "mlir/Tools/mlir-opt/MlirOptMain.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/ToolOutputFile.h"

// #include "Dialect/profiling/profilingDialect.h"
// #include "Dialect/profiling/profilingOps.h"
#include <cstdint>
#include <dlfcn.h> // for dlopen, dlsym, dlclose
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <thread>

#include "mlir_profiler/TimeManager.h"

extern "C" void _mlir_ciface_timingStart(uint64_t);

extern "C" void _mlir_ciface_timingEnd(uint64_t);

extern "C" void _mlir_ciface_printtest();

class Profiler {

public:
  Profiler(std::filesystem::path mlirFilePath) : mlirFilePath(mlirFilePath) {
    /* init MLIRContext */
    mlir::DialectRegistry registry;
    // Register all MLIR core dialects.
    mlir::registerAllDialects(registry);
    context.appendDialectRegistry(registry);
    // mlir::registerAllExtensions(registry);

    /*--Register dialects in custom project.--*/

    // context.getOrLoadDialect<profiling::ProfilingDialect>();

    // registry.insert<profiling::ProfilingDialect>();

    context.appendDialectRegistry(registry);

    /* init TimeManager */
    if (!timeManager) {
      timeManager = std::make_unique<TimeManager>();
    }
  }

  ~Profiler() = default;

  std::string instrument(const std::string &targetDialect);

  void compile(const std::string &target);

  template <typename Func>
  Func loadLib(const std::string &libpath, const std::string &funcName) {

    // Invoke the dynamic link library
    void *handle =
        dlopen(libpath.c_str(), RTLD_LAZY | RTLD_GLOBAL); // invoke .so lib
    if (!handle) {
      std::cerr << "Failed to load shared library: " << dlerror() << std::endl;
      return 0;
    }

    Func fptr = reinterpret_cast<Func>(dlsym(handle, funcName.c_str()));
    char *error = dlerror();
    if (error != NULL) {
      std::cerr << "Failed to load symbol: " << error << std::endl;
      dlclose(handle);
      return nullptr;
    }

    std::cout << "Load success!" << std::endl;
    return fptr;
  }

  void outputResult(const std::string &resultFilepath) {
    timeManager->processTimingData(resultFilepath);
  }

  static TimeManager &getTimeManager() { return *timeManager; }

private:
  mlir::OwningOpRef<mlir::ModuleOp> parseMLIRsrcfile(std::string mlirFilePath);

  void makeTarget(const std::string &target);

private:
  mlir::MLIRContext context;

  std::filesystem::path mlirFilePath;

  static std::unique_ptr<TimeManager> timeManager;
};

#endif // ML_PROFILER_PROFILER_H
