# MLProf

A profiling tool for MLIR-based machine learning models.

## Prerequisites

- Git
- CMake (version 3.15 or higher)
- C++ compiler with C++17 support
- Python 3.6+
- Ninja (optional, for faster builds)

## Setup Instructions

### 1. Clone the Repository

```bash
git clone https://github.com/LiuYang328/MLProf.git
cd MLProf
```

### 2. Initialize LLVM Submodule

This project uses LLVM as a git submodule. Initialize and update the submodule:

```bash
# Add LLVM as a submodule (if not already added)
git submodule add https://github.com/llvm/llvm-project.git third-party/llvm-project

# Initialize and update all submodules
git submodule update --init --recursive
```

### 3. Build LLVM

```bash
$ mkdir llvm/build
$ cd llvm/build
$ cmake -G Ninja ../llvm \
    -DLLVM_ENABLE_PROJECTS="mlir;clang;lld" \
    -DLLVM_TARGETS_TO_BUILD="host;RISCV;NVPTX" \
    -DMLIR_ENABLE_CUDA_RUNNER=ON \
    -DLLVM_ENABLE_ASSERTIONS=ON \
    -DCMAKE_BUILD_TYPE=RELEASE \
    -DMLIR_ENABLE_BINDINGS_PYTHON=ON \
    -DPython3_EXECUTABLE=$(which python3)

$ ninja check-mlir check-clang
```

### 4. Build the Project

```bash
# Return to project root

cd MLProf

# Create build directory
mkdir build && cd build

# Configure project
cmake .. -DLLVM_DIR=../llvm/build/lib/cmake/llvm \
         -DMLIR_DIR=../llvm/build/lib/cmake/mlir

# Build the project
make -j$(nproc)
```



## run example

```
cd examples/LeNet
```
and then 

run  profiler-main

```
./profiler-main
```


## Directory Structure

```
MLProf/
├── CMakeLists.txt
├── README.md
├── src/
├── include/
├── examples/
│   └── LeNet/                 # LeNet example
├── llvm/                      # LLVM submodule
└── build/                     # Build directory
```




