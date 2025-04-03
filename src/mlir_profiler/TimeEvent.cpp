#include "mlir_profiler/TimeEvent.h"
#include <chrono>


double TimeEvent::getCurrentTimeStamp() {

  auto now = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::time_point_cast<std::chrono::microseconds>(now);
  return time.time_since_epoch().count() / 1'000.0; // convert to ms
}


