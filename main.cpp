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


  /* init Profiler */
  Profiler profiler(
    "/home/liuyang/project/mlir-profiler/buddy-mlir/examples/profiler-lenet/log.mlir");
    
  std::cout << "start instrument"<< std::endl;

  return 0;
}
