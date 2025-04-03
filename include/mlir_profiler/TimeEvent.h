#ifndef TIME_EVENT_H
#define TIME_EVENT_H

#include <iostream>
#include <mlir/IR/Operation.h>


class TimeEvent {
public:
  using OpPtr = mlir::Operation *;

  TimeEvent() = default; // 声明默认构造函数
  TimeEvent(OpPtr opPtr)
      : opPtr(opPtr), opName(opPtr->getName().getStringRef().str()),
        startTimestamp(0), endTimestamp(0), duration(0) {}
        
  TimeEvent(const TimeEvent &) = default;
  TimeEvent(TimeEvent &&) = default;

  void setStartTimestamp() {
    // std::cout << "setStartTimestamp" << std::endl;
    startTimestamp = getCurrentTimeStamp();
  };
  double getStartTimestamp() const { return startTimestamp; };

  void setEndTimestamp() {
    // std::cout << "setEndTimestamp" << std::endl;
    endTimestamp = getCurrentTimeStamp();
  };

  double getEndTimestamp() const { return endTimestamp; };

  double getInterval() const { return endTimestamp - startTimestamp; }

  double getDuration() const { return duration; }

  void setDuration(double d) { duration = d; }

  OpPtr getOpPtr() const { return opPtr; }

  std::string getOpName() const { return opName; }

private:
  double getCurrentTimeStamp();

  OpPtr opPtr;
  std::string opName;
  double startTimestamp;
  double endTimestamp;
  double duration;
};

#endif // TIME_EVENT_H