//===- buddy-lenet-main.cpp -----------------------------------------------===//
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//===----------------------------------------------------------------------===//

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <limits>
#include <string>
#include <utility>
#include <vector>

#include <cstdint>
#include <dlfcn.h> // for dlopen, dlsym, dlclose
#include <functional>
#include <iostream>
#include <thread>

#include <Profiler.h>
#include <chrono>



/// Declare LeNet forward function.
extern "C" void _mlir_ciface_forward();


int main() {
  // Print the title of this example.
  std::cout << "=== MLProf LeNet Example ===" << std::endl;

  /* init Profiler */
  std::cout << "Initializing profiler..." << std::endl;
  Profiler profiler(
    "examples/LeNet/lenet-test.mlir");
    
  std::cout << "Starting instrumentation..." << std::endl;
  profiler.instrument("tosa");
  std::cout << "Compiling MLIR code..." << std::endl;
  profiler.compile("examples");

  /* define MLIR Function type */
  typedef void (*MLIRFuncType)( );

  /* Load Shared Library */
  std::cout << "Loading shared library..." << std::endl;
  MLIRFuncType _mlir_ciface_forward =
      profiler.loadLib<MLIRFuncType>("libexamples.so", "_mlir_ciface_forward");

  std::cout << "Executing forward pass..." << std::endl;
  _mlir_ciface_forward( );
  std::cout << "Forward pass completed." << std::endl;

  std::cout << "Saving profiling results to result.json..." << std::endl;
  profiler.outputResult("result.json");
  std::cout << "Results have been saved successfully." << std::endl;

  std::cout << "Program execution completed successfully." << std::endl;
  return 0;
}
