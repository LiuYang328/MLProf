#!/bin/bash
BUDDY_BUILD_DIR := ../../build/
LLVM_BUILD_DIR := /root/repos/MLProf/llvm/build-6c59f0e1b0fb
BUDDY_OPT := ${BUDDY_BUILD_DIR}/bin/buddy-opt
MLIR_OPT := ${LLVM_BUILD_DIR}//bin/mlir-opt
MLIR_TRANSLATE := ${LLVM_BUILD_DIR}/bin/mlir-translate
MLIR_CPU_RUNNER := ${LLVM_BUILD_DIR}/bin/mlir-cpu-runner
LLC := ${LLVM_BUILD_DIR}/bin/llc
OPT_FLAG := -O3
LLVM_LIB_DIR = ${LLVM_BUILD_DIR}/lib



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

buddy-lenet-lower:
	@${MLIR_OPT} ./lenet-test.mlir \
		-pass-pipeline "builtin.module(func.func(tosa-to-linalg-named, tosa-to-linalg, tosa-to-tensor, tosa-to-arith))" | \
	${MLIR_OPT} \
		-eliminate-empty-tensors \
		-convert-tensor-to-linalg \
		-one-shot-bufferize \
		-convert-linalg-to-affine-loops \
		-lower-affine \
		-buffer-deallocation \
		-finalizing-bufferize \
		-convert-vector-to-scf \
		-expand-strided-metadata \
		-convert-vector-to-llvm \
		-convert-arith-to-llvm \
		-finalize-memref-to-llvm \
		-convert-scf-to-cf \
		-convert-arith-to-llvm \
		-convert-func-to-llvm \
		-reconcile-unrealized-casts \
		-o ./log.mlir

buddy-lenet-lower-fake:
	@${MLIR_OPT} ./fake-lenet.mlir \
		-pass-pipeline "builtin.module(func.func(tosa-to-linalg-named, tosa-to-linalg, tosa-to-tensor, tosa-to-arith))" | \
	${MLIR_OPT} \
		-eliminate-empty-tensors \
		-convert-tensor-to-linalg \
		-one-shot-bufferize \
		-convert-linalg-to-affine-loops \
		-lower-affine \
		-buffer-deallocation \
		-finalizing-bufferize \
		-convert-vector-to-scf \
		-expand-strided-metadata \
		-convert-vector-to-llvm \
		-convert-arith-to-llvm \
		-finalize-memref-to-llvm \
		-convert-scf-to-cf \
		-convert-arith-to-llvm \
		-convert-func-to-llvm \
		-reconcile-unrealized-casts \
		-o ./log.mlir

buddy-lenet-translate:
	@${MLIR_OPT} ./lenet-test.mlir \
		-pass-pipeline "builtin.module(func.func(tosa-to-linalg-named, tosa-to-linalg, tosa-to-tensor, tosa-to-arith))" | \
	${MLIR_OPT} \
		-eliminate-empty-tensors \
		-convert-tensor-to-linalg \
		-one-shot-bufferize \
		-convert-linalg-to-affine-loops \
		-lower-affine \
		-convert-vector-to-scf \
		-expand-strided-metadata \
		-convert-vector-to-llvm \
		-convert-arith-to-llvm \
		-finalize-memref-to-llvm \
		-convert-scf-to-cf \
		-convert-arith-to-llvm \
		-convert-func-to-llvm \
		-reconcile-unrealized-casts | \
	${MLIR_TRANSLATE} -mlir-to-llvmir -o log.ll


buddy-lenet-run:
	@${MLIR_OPT} ./fake-lenet.mlir \
		-pass-pipeline "builtin.module(func.func(tosa-to-linalg-named, tosa-to-linalg, tosa-to-tensor, tosa-to-arith))" | \
	${MLIR_OPT} \
		-eliminate-empty-tensors \
		-convert-tensor-to-linalg \
		-linalg-bufferize \
		-convert-linalg-to-affine-loops \
		-lower-affine \
		-func-bufferize \
		-arith-bufferize \
		-tensor-bufferize \
		-buffer-deallocation \
		-finalizing-bufferize \
		-convert-vector-to-scf \
		-expand-strided-metadata \
		-convert-vector-to-llvm \
		-convert-arith-to-llvm \
		-finalize-memref-to-llvm \
		-convert-scf-to-cf \
		-convert-arith-to-llvm \
		-convert-func-to-llvm \
		-reconcile-unrealized-casts | \
	${MLIR_CPU_RUNNER} ${OPT_FLAG} -e main -entry-point-result=void \
		-shared-libs=${MLIR_RUNNER_UTILS} -shared-libs=${MLIR_C_RUNNER_UTILS}

buddy-lenet-opt-run:
	@${BUDDY_OPT} ./fake-lenet.mlir \
		-pass-pipeline "builtin.module(func.func(tosa-to-linalg-named, tosa-to-linalg, tosa-to-tensor, tosa-to-arith))" | \
	${BUDDY_OPT} \
		-eliminate-empty-tensors \
		-convert-tensor-to-linalg \
		-linalg-bufferize \
		-batchmatmul-optimize \
		-convert-linalg-to-affine-loops \
		-lower-affine \
		-func-bufferize \
		-arith-bufferize \
		-tensor-bufferize \
		-buffer-deallocation \
		-finalizing-bufferize \
		-convert-vector-to-scf \
		-expand-strided-metadata \
		-convert-vector-to-llvm \
		-convert-arith-to-llvm \
		-finalize-memref-to-llvm \
		-convert-scf-to-cf \
		-convert-arith-to-llvm \
		-convert-func-to-llvm \
		-reconcile-unrealized-casts | \
	${MLIR_CPU_RUNNER} ${OPT_FLAG} -e main -entry-point-result=void \
		-shared-libs=${MLIR_RUNNER_UTILS} -shared-libs=${MLIR_C_RUNNER_UTILS}



#!/bin/bash
BUDDY_BUILD_DIR := ../../build
LLVM_BUILD_DIR := /root/repos/MLProf/llvm/build-6c59f0e1b0fb
MLIR_OPT := ${LLVM_BUILD_DIR}/bin/mlir-opt
MLIR_TRANSLATE := ${LLVM_BUILD_DIR}/bin/mlir-translate
MLIR_CPU_RUNNER := ${LLVM_BUILD_DIR}/bin/mlir-cpu-runner
LLC := ${LLVM_BUILD_DIR}/bin/llc
OPT_FLAG := -O0
LLVM_TOOLS_BINARY_DIR = ${LLVM_BUILD_DIR}/bin


ifeq ($(shell uname),Linux)
MLIR_RUNNER_UTILS := ${LLVM_BUILD_DIR}/lib/libmlir_runner_utils.so
MLIR_C_RUNNER_UTILS := ${LLVM_BUILD_DIR}/lib/libmlir_c_runner_utils.so
MTRIPLE := x86_64-unknown-linux-gnu
else ifeq ($(shell uname),Darwin)
MLIR_RUNNER_UTILS := ${LLVM_BUILD_DIR}/lib/libmlir_runner_utils.dylib
MLIR_C_RUNNER_UTILS := ${LLVM_BUILD_DIR}/lib/libmlir_c_runner_utils.dylib
MTRIPLE := x86_64-apple-darwin
endif

CMAKE_CURRENT_BINARY_DIR := ${BUDDY_BUILD_DIR}/examples/LeNet



# ************************ cpu************************


# 构建 forward.o
profiling-forward:
	${BUDDY_OPT} ${CMAKE_CURRENT_BINARY_DIR}/forward.mlir \
		-pass-pipeline "builtin.module(func.func(tosa-to-linalg-named, tosa-to-linalg, tosa-to-tensor, tosa-to-arith), empty-tensor-to-alloc-tensor, convert-elementwise-to-linalg, arith-bufferize, func.func(linalg-bufferize, tensor-bufferize), func-bufferize)" | \
	${BUDDY_OPT} -pass-pipeline "builtin.module(func.func(buffer-deallocation-simplification, convert-linalg-to-loops), eliminate-empty-tensors, func.func(llvm-request-c-wrappers), convert-math-to-llvm, convert-math-to-libm, convert-scf-to-cf, convert-arith-to-llvm, expand-strided-metadata, finalize-memref-to-llvm, convert-func-to-llvm, reconcile-unrealized-casts)" | \
	${LLVM_TOOLS_BINARY_DIR}/mlir-translate -mlir-to-llvmir | \
	${LLVM_TOOLS_BINARY_DIR}/llvm-as | \
	${LLVM_TOOLS_BINARY_DIR}/llc -filetype=obj -relocation-model=pic -O0 -o ${CMAKE_CURRENT_BINARY_DIR}/forward.o
	${LLVM_TOOLS_BINARY_DIR}/clang -shared -o libforward.so ${CMAKE_CURRENT_BINARY_DIR}/forward.o ${CMAKE_CURRENT_BINARY_DIR}/subgraph0.o /home/gaoshihao/project/buddy-mlir/build-profiler/lib/libBuddyRuntime.a ${BUDDY_LIB_DIR}/libStaticMLIRCRunnerUtils.a ${BUDDY_LIB_DIR}/libStaticMLIRRunnerUtils.a 


# 构建 subgraph0.o
profiling-subgraph0:
	${BUDDY_OPT} ${CMAKE_CURRENT_BINARY_DIR}/subgraph0_instrumented.mlir \
		-pass-pipeline "builtin.module(func.func(tosa-to-linalg-named, tosa-to-linalg, tosa-to-tensor, tosa-to-arith))" | \
	${BUDDY_OPT} -eliminate-empty-tensors -convert-tensor-to-linalg  -linalg-bufferize -convert-linalg-to-affine-loops -lower-affine -func-bufferize-dynamic-offset -arith-bufferize -tensor-bufferize -buffer-deallocation -finalizing-bufferize -convert-vector-to-scf -expand-strided-metadata -convert-vector-to-llvm -convert-arith-to-llvm -finalize-memref-to-llvm -convert-scf-to-cf -llvm-request-c-wrappers -convert-arith-to-llvm -convert-func-to-llvm -reconcile-unrealized-casts | \
	${LLVM_TOOLS_BINARY_DIR}/mlir-translate -mlir-to-llvmir | \
	tee ${CMAKE_CURRENT_BINARY_DIR}/subgraph0.ll | \
	${LLVM_TOOLS_BINARY_DIR}/llvm-as | \
	${LLVM_TOOLS_BINARY_DIR}/llc -filetype=obj -relocation-model=pic -O0 -o ${CMAKE_CURRENT_BINARY_DIR}/subgraph0.o





# profiling-examples:
# 	${MLIR_OPT} /root/repos/MLProf/examples/LeNet/lenet-test.mlir \
# 		--convert-vector-to-scf --lower-affine --convert-scf-to-cf -llvm-request-c-wrappers \
# 		--convert-vector-to-llvm --finalize-memref-to-llvm --convert-func-to-llvm  \
# 		--reconcile-unrealized-casts | \
#  	${LLVM_TOOLS_BINARY_DIR}/mlir-translate -mlir-to-llvmir| \
#  	${LLVM_TOOLS_BINARY_DIR}/llvm-as | \
# 	${LLVM_TOOLS_BINARY_DIR}/llc -filetype=obj -relocation-model=pic -O0 -o ${CMAKE_CURRENT_BINARY_DIR}/affineload.o
# 	${LLVM_TOOLS_BINARY_DIR}/clang++ -shared -o libaffineload.so ${CMAKE_CURRENT_BINARY_DIR}/affineload.o  /home/liuyang/project/mlir-profiler/buddy-mlir/build/lib/libBuddyRuntime.a ${BUDDY_LIB_DIR}/libStaticMLIRCRunnerUtils.a ${BUDDY_LIB_DIR}/libStaticMLIRRunnerUtils.a 



profiling-examples:
	@echo "Converting TOSA to Linalg and lowering to LLVM IR..."
	@mkdir -p ${CMAKE_CURRENT_BINARY_DIR}
	${MLIR_OPT} /root/repos/MLProf/examples/LeNet/lenet-test_instrumented.mlir \
		-pass-pipeline "builtin.module(func.func(tosa-to-linalg-named, tosa-to-linalg, tosa-to-tensor, tosa-to-arith))"| \
	${MLIR_OPT} \
		-convert-tensor-to-linalg \
		-linalg-bufferize \
		-convert-linalg-to-affine-loops \
		-lower-affine \
		-func-bufferize \
		-arith-bufferize \
		-tensor-bufferize \
		-llvm-request-c-wrappers\
		-convert-vector-to-scf \
		-expand-strided-metadata \
		-convert-vector-to-llvm \
		-convert-arith-to-llvm \
		-finalize-memref-to-llvm \
		-convert-scf-to-cf \
		-convert-arith-to-llvm \
		-convert-func-to-llvm \
		-reconcile-unrealized-casts | \
 	${LLVM_TOOLS_BINARY_DIR}/mlir-translate -mlir-to-llvmir| \
 	${LLVM_TOOLS_BINARY_DIR}/llvm-as | \
	${LLVM_TOOLS_BINARY_DIR}/llc -filetype=obj -relocation-model=pic -O0 -o ${CMAKE_CURRENT_BINARY_DIR}/examples.o
	${LLVM_TOOLS_BINARY_DIR}/clang++ -shared -o libexamples.so ${CMAKE_CURRENT_BINARY_DIR}/examples.o  /root/repos/MLProf/build/src/mlir_profiler/libProfilerRuntime.so 
