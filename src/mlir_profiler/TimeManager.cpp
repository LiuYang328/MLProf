#include "mlir_profiler/TimeManager.h"

void TimeManager::processTimingData(const std::string &outputFilepath) {

  if (events.empty()) {
    std::cerr << "Events list is empty." << std::endl;
    return;
  }

  std::map<std::string, double> times;

  double duration = 0;

  int size = events.size();
  std::cout << size << std::endl;
  for (int i = 0; i < size; i++) {
    if (events[i] == nullptr) {
      std::cerr << "Null pointer found in events at index " << i << std::endl;
      continue;
    }
    mlir::Operation *opPtr = (events[i])->getOpPtr();
    if (opPtr == nullptr) {
      std::cerr << "Null pointer found in opPtr at index " << i << std::endl;
      continue;
    }

    std::string opName = events[i]->getOpName();

    std::cout << opName << std::endl;
    duration = (events[i])->getDuration();
    std::cout << "OP name: " << opName << " duration: " << duration
              << std::endl;
    if (times.find(opName) != times.end())
      times[opName] += duration;
    else
      times[opName] = duration;
  }
  // 在循环后添加
  std::ofstream outFile(outputFilepath);
  if (!outFile.is_open()) {
    std::cerr << "Failed to open output file: " << outputFilepath << std::endl;
    return;
  }

  outFile << "{" << std::endl;
  bool first = true;
  for (const auto &pair : times) {
    if (!first)
      outFile << "," << std::endl;
    outFile << "  \"" << pair.first << "\": " << pair.second;
    first = false;
  }
  outFile << std::endl << "}" << std::endl;

  outFile.close();
}
