#include "mlir_profiler/TimeEvent.h"
#include <chrono>


double TimeEvent::getCurrentTimeStamp() {

  auto now = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::time_point_cast<std::chrono::microseconds>(now);
  std::cout << "time: " << time.time_since_epoch().count() << std::endl;
  return time.time_since_epoch().count(); // convert to ms
}


