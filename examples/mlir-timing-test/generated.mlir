"builtin.module"() ({
  "func.func"() <{function_type = (memref<?x?xf32>, memref<?x?xf32>) -> memref<?x?xf32>, sym_name = "matmul"}> ({
  ^bb0(%arg0: memref<?x?xf32>, %arg1: memref<?x?xf32>):
    %0 = "arith.constant"() <{value = 0 : index}> : () -> index
    %1 = "arith.constant"() <{value = 1 : index}> : () -> index
    %2 = "arith.constant"() <{value = 0.000000e+00 : f32}> : () -> f32
    %3 = "memref.dim"(%arg0, %0) : (memref<?x?xf32>, index) -> index
    %4 = "memref.dim"(%arg1, %1) : (memref<?x?xf32>, index) -> index
    %5 = "memref.alloc"(%3, %4) <{operandSegmentSizes = array<i32: 2, 0>}> : (index, index) -> memref<?x?xf32>
    "profiling.scope"() ({
      "linalg.fill"(%2, %5) <{operandSegmentSizes = array<i32: 1, 1>}> ({
      ^bb0(%arg5: f32, %arg6: f32):
        "linalg.yield"(%arg5) : (f32) -> ()
      }) : (f32, memref<?x?xf32>) -> ()
    }) : () -> ()
    "profiling.scope"() ({
      "linalg.matmul"(%arg0, %arg1, %5) <{operandSegmentSizes = array<i32: 2, 1>}> ({
      ^bb0(%arg2: f32, %arg3: f32, %arg4: f32):
        %6 = "arith.mulf"(%arg2, %arg3) <{fastmath = #arith.fastmath<none>}> : (f32, f32) -> f32
        %7 = "arith.addf"(%arg4, %6) <{fastmath = #arith.fastmath<none>}> : (f32, f32) -> f32
        "linalg.yield"(%7) : (f32) -> ()
      }) {linalg.memoized_indexing_maps = [affine_map<(d0, d1, d2) -> (d0, d2)>, affine_map<(d0, d1, d2) -> (d2, d1)>, affine_map<(d0, d1, d2) -> (d0, d1)>]} : (memref<?x?xf32>, memref<?x?xf32>, memref<?x?xf32>) -> ()
    }) : () -> ()
    "func.return"(%5) : (memref<?x?xf32>) -> ()
  }) : () -> ()
}) : () -> ()