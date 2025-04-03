module {
  func.func @main() {
    profiler.start()
    %cst = arith.constant dense<[[8.000000e+00]]> : tensor<1x1xf32>
    profiler.end()
    profiler.start()
    %cst_0 = arith.constant dense<1.000000e+00> : tensor<3x3xf32>
    profiler.end()
    profiler.start()
    %cst_1 = arith.constant dense<[0.000000e+00, 1.000000e+00, 2.000000e+00]> : tensor<3xf32>
    profiler.end()
    profiler.start()
    %cst_2 = arith.constant dense<[1, 0]> : tensor<2xi64>
    profiler.end()
    profiler.start()
    %cst_3 = arith.constant dense<1.000000e+00> : tensor<3x3xf32>
    profiler.end()
    profiler.start()
    %0 = tensor.empty() : tensor<3x3xf32>
    profiler.end()
    profiler.start()
    %1 = linalg.generic {indexing_maps = [#map, #map1], iterator_types = ["parallel", "parallel"]} ins(%cst_1 : tensor<3xf32>) outs(%0 : tensor<3x3xf32>) {
      ^bb0(%in: f32, %out: f32):
      linalg.yield %in : f32
    } -> tensor<3x3xf32>
    profiler.end()
    profiler.start()
    %2 = linalg.matmul ins(%cst, %cst_3 : tensor<3x3xf32>, tensor<3x3xf32>) outs(%1 : tensor<3x3xf32>) -> tensor<3x3xf32>
    profiler.end()
    profiler.start()
    %cast = tensor.cast %2 : tensor<3x3xf32> to tensor<*xf32>
    profiler.end()
    profiler.start()
    return
    profiler.end()

    call @rtclock() : () -> ()
    
    gpu.conv2d()

    
    call @rtclock() : () -> ()    

  }
}




profiler.time {

  arith.add

}


profiler.time {

  arith.constant
}