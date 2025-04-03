//===- ToyCombine.cpp - Toy High Level Optimizer --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements a set of simple combiners for optimizing operations in
// the Toy dialect.
//
//===----------------------------------------------------------------------===//

#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/IR/Value.h"
#include "profiling/profilingDialect.h"
#include "profiling/profilingOps.h"

#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/IR/BuiltinDialect.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/Diagnostics.h"
#include "mlir/IR/DialectRegistry.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/IR/ValueRange.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Support/TypeID.h"

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Transforms/DialectConversion.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/Sequence.h"
#include "llvm/Support/Casting.h"
#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>

using namespace mlir;

struct ScopeEliminate : public OpRewritePattern<profiling::ScopeOp> {
public:
  // using OpRewritePattern<profiling::ScopeOp>::OpRewritePattern;

  ScopeEliminate(mlir::MLIRContext *context)
      : OpRewritePattern<profiling::ScopeOp>(context) {}

  LogicalResult matchAndRewrite(profiling::ScopeOp op,
                                PatternRewriter &rewriter) const override {

    auto &scopeinterregion = op.getRegion();
    int regionnum = op->getNumRegions();
    std::cout << "regionnum: " << regionnum << std::endl;

    std::string name = op->getName().getStringRef().str();

    std::cout << "ScopeEliminate: " << name << std::endl;
    // rewriter.eraseOp(op);

    op.walk([&](Operation *interop) {
      std::cout << "op: " << interop->getName().getStringRef().str()
                << std::endl;
      if (interop->getName().getStringRef().str() != "profiling.scope") {
        std::cout << "move op" << std::endl;
        rewriter.moveOpBefore(interop, op);
      }
    });

    std::cout << "ScopeEliminate finished" << std::endl;

    return success();
  }
};

/// Register our patterns as "canonicalization" patterns on the TransposeOp so
/// that they can be picked up by thec framework.
void profiling::ScopeOp::getCanonicalizationPatterns(RewritePatternSet &results,
                                                     MLIRContext *context) {
  results.add<ScopeEliminate>(context);
}

// void ScopeLoweringPass::runOnOperation() {
//   // The first thing to define is the conversion target. This will define the
//   // final target for this lowering.

//   mlir::ConversionTarget target(*getContext());

//   // We define the specific operations, or dialects, that are legal targets
//   for
//   // this lowering. In our case, we are lowering to a combination of the
//   // `Affine`, `Arith`, `Func`, and `MemRef` dialects.
//   target.addLegalDialect<affine::AffineDialect, arith::ArithDialect,
//                          func::FuncDialect, memref::MemRefDialect>();

//   // We also define the Toy dialect as Illegal so that the conversion will
//   fail
//   // if any of these operations are *not* converted. Given that we actually
//   want
//   // a partial lowering, we explicitly mark the Toy operations that don't
//   want
//   // to lower, `toy.print`, as *legal*. `toy.print` will still need its
//   operands
//   // to be updated though (as we convert from TensorType to MemRefType), so
//   we
//   // only treat it as `legal` if its operands are legal.
//   target.addIllegalDialect<profiling::ProfilingDialect>();
// }

//===----------------------------------------------------------------------===//
// Scope RewritePatterns: Scope operations
//===----------------------------------------------------------------------===//

// struct TransposeOpLowering : public ConversionPattern {
//   TransposeOpLowering(MLIRContext *ctx)
//       : ConversionPattern(toy::TransposeOp::getOperationName(), 1, ctx) {}

//   LogicalResult
//   matchAndRewrite(Operation *op, ArrayRef<Value> operands,
//                   ConversionPatternRewriter &rewriter) const final {
//     auto loc = op->getLoc();
//     lowerOpToLoops(op, operands, rewriter,
//                    [loc](OpBuilder &builder, ValueRange memRefOperands,
//                          ValueRange loopIvs) {
//                      // Generate an adaptor for the remapped operands of the
//                      // TransposeOp. This allows for using the nice named
//                      // accessors that are generated by the ODS.
//                      toy::TransposeOpAdaptor
//                      transposeAdaptor(memRefOperands); Value input =
//                      transposeAdaptor.getInput();

//                      // Transpose the elements by generating a load from the
//                      // reverse indices.
//                      SmallVector<Value, 2>
//                      reverseIvs(llvm::reverse(loopIvs)); return
//                      builder.create<affine::AffineLoadOp>(loc, input,
//                                                                  reverseIvs);
//                    });
//     return success();
//   }
// };
