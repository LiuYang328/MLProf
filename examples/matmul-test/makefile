#!/bin/bash
LLVM_BUILD_DIR := /root/third-lib/llvm-project/build-19.1.7
MLIR_OPT := ${LLVM_BUILD_DIR}/bin/mlir-opt
MLIR_TRANSLATE := ${LLVM_BUILD_DIR}/bin/mlir-translate
MLIR_CPU_RUNNER := ${LLVM_BUILD_DIR}/bin/mlir-cpu-runner
LLC := ${LLVM_BUILD_DIR}/bin/llc
OPT_FLAG := -O3
CLANG := ${LLVM_BUILD_DIR}/bin/clang
MLIR_LIB := /root/third-lib/llvm-project/build-19.1.7/lib/

ifeq ($(shell uname),Linux)
MLIR_RUNNER_UTILS := ${LLVM_BUILD_DIR}/lib/libmlir_runner_utils.so
MLIR_C_RUNNER_UTILS := ${LLVM_BUILD_DIR}/lib/libmlir_c_runner_utils.so
MLIR_ASYNC_RUNTIME := ${LLVM_BUILD_DIR}/lib/libmlir_async_runtime.so
MTRIPLE := x86_64-unknown-linux-gnu
else ifeq ($(shell uname),Darwin)
MLIR_RUNNER_UTILS := ${LLVM_BUILD_DIR}/lib/libmlir_runner_utils.dylib
MLIR_C_RUNNER_UTILS := ${LLVM_BUILD_DIR}/lib/libmlir_c_runner_utils.dylib
MLIR_ASYNC_RUNTIME := ${LLVM_BUILD_DIR}/lib/libmlir_async_runtime.dylib
MTRIPLE := x86_64-apple-darwin
endif

matmul-lower:
	@${MLIR_OPT} ./matmul-vs-matvec.mlir \
		-convert-linalg-to-loops \
		-convert-scf-to-cf \
		-expand-strided-metadata \
		-lower-affine \
		-convert-arith-to-llvm \
		-finalize-memref-to-llvm \
		-convert-func-to-llvm \
		-reconcile-unrealized-casts  \
		-o ./log.mlir

matmul-translate:
	@${MLIR_OPT} ./matmul-vs-matvec.mlir \
		-convert-linalg-to-loops \
		-convert-scf-to-cf \
		-expand-strided-metadata \
		-lower-affine \
		-convert-arith-to-llvm \
		-finalize-memref-to-llvm \
		-convert-func-to-llvm \
		-reconcile-unrealized-casts | \
	${MLIR_TRANSLATE} -mlir-to-llvmir -o log.ll


matmul-run:
	@${MLIR_OPT} ./matmul-vs-matvec.mlir \
		-convert-linalg-to-loops \
		-convert-scf-to-cf \
		-expand-strided-metadata \
		-lower-affine \
		-convert-arith-to-llvm \
		-finalize-memref-to-llvm \
		-convert-func-to-llvm \
		-reconcile-unrealized-casts | \
	${MLIR_CPU_RUNNER} ${OPT_FLAG} -e main -entry-point-result=void \
		-shared-libs=${MLIR_RUNNER_UTILS} -shared-libs=${MLIR_C_RUNNER_UTILS}



matmul-time-run:
	@${MLIR_OPT} ./matmul-callfunc-test.mlir \
		-convert-linalg-to-loops \
		-convert-scf-to-cf \
		-expand-strided-metadata \
		-lower-affine \
		-convert-arith-to-llvm \
		-finalize-memref-to-llvm \
		-convert-func-to-llvm \
		-reconcile-unrealized-casts \
		-llvm-request-c-wrappers  | \
	${MLIR_CPU_RUNNER} ${OPT_FLAG} -e main -entry-point-result=void \
		-shared-libs=${MLIR_RUNNER_UTILS} -shared-libs=${MLIR_C_RUNNER_UTILS}  -shared-libs=/root/myproject/MLIR-Profiler/MLProfiler/build/src/mlir_profiler/libProfilerRuntime.so 




matmul-time-run-aot:
	@${MLIR_OPT} ./matmul-callfunc-test.mlir \
		-convert-linalg-to-loops \
		-convert-scf-to-cf \
		-expand-strided-metadata \
		-lower-affine \
		-convert-arith-to-llvm \
		-finalize-memref-to-llvm \
		-llvm-request-c-wrappers \
		-convert-func-to-llvm \
		-reconcile-unrealized-casts   | \
	${MLIR_TRANSLATE} --mlir-to-llvmir -o log.ll

	${CLANG} log.ll -O3 \
		-L${MLIR_LIB} -lmlir_runner_utils -lmlir_c_runner_utils \
		-L/root/myproject/MLIR-Profiler/MLProfiler/build/src/mlir_profiler  -lProfilerRuntime \
		-o a.out

	@export LD_LIBRARY_PATH=${MLIR_LIB}:/root/myproject/MLIR-Profiler/MLProfiler/build/src/mlir_profiler:$LD_LIBRARY_PATH && ./a.out


clean:
	rm -f *.ll *.out