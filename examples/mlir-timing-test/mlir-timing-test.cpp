#include "mlir/Support/Timing.h"
#include <chrono>
#include <cstdio>
#include <thread>

using namespace mlir;

// 模拟一个耗时任务
void simulatedWork(int milliseconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

double getCurrentTimeStamp() {

    auto now = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::time_point_cast<std::chrono::microseconds>(now);
    return time.time_since_epoch().count() / 1'000.0; // convert to ms
  }


int main() {
  // 1. 创建默认计时管理器
  DefaultTimingManager timingManager;
  
  // 2. 启用计时（默认禁用）
  timingManager.setEnabled(true);
  
  // 3. 设置显示模式为树状结构
  timingManager.setDisplayMode(DefaultTimingManager::DisplayMode::Tree);
  double t1 = getCurrentTimeStamp();

  {
    // 4. 创建根计时作用域（自动启动计时）
    TimingScope rootScope = timingManager.getRootScope();

    // 5. 第一个任务
    {
      TimingScope task1 = rootScope.nest("DataProcessing");
      simulatedWork(120);
    }

    // 6. 第二个任务（包含子任务）
    {
      TimingScope task2 = rootScope.nest("NetworkOperations");
      
      {
        TimingScope subtask = task2.nest("DNSLookup");
        simulatedWork(50);
      }
      
      {
        TimingScope subtask = task2.nest("TLSHandshake");
        simulatedWork(80);
      }
    }

    // 7. 第三个隐藏任务（不在报告中显示）
    {
      TimingScope hiddenTask = rootScope.nest("HiddenTask");
      hiddenTask.hide();
      simulatedWork(30);
    }
  } // 根作用域在此结束，自动停止所有计时

  // 8. 打印计时结果
  timingManager.print();

  printf("done\n");

  
  double t2 = getCurrentTimeStamp();

  double t3 = t2 - t1;
  
  printf("t3: %f\n", t3);


  return 0;
}