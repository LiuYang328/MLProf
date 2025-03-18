
#include <fstream>
#include <iostream>
#include <json.hpp>
#include <map>
#include <mlir/IR/Operation.h>
#include <string>
#include <unordered_map>
#include <vector>

class TimeManager {
public:
  TimeManager() = default;
  ~TimeManager() {
    for (TimeEvent *e : events) {
      delete e;
    }
  }
  TimeManager(const TimeManager &) = delete;
  TimeManager &operator=(const TimeManager &) = delete;

  void timingStart(TimeEvent *e) { (*e).setStartTimestamp(); }

  void timingEnd(TimeEvent *e) {
    (*e).setEndTimestamp();
    (*e).updateDuration();
  }

  void addEvent(TimeEvent *event) { events.push_back(event); }

  TimeEvent *eventsBack() { return events.back(); }

  // process data
  void processTimingData(const std::string &outputFilepath);

private:
  // save all timeEvents
  std::vector<TimeEvent *> events;
};

class TimeEvent {
public:

  TimeEvent(mlir::Operation * opPtr)
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

  void updateDuration() {
    // std::cout << "updateDuration" << std::endl;
    double interval = getInterval();
    double curDuration = getDuration();
    setDuration(curDuration + interval);
  }

  double getEndTimestamp() const { return endTimestamp; };

  double getInterval() const { return endTimestamp - startTimestamp; }

  double getDuration() const { return duration; }

  void setDuration(double d) { duration = d; }

  mlir::Operation * getOpPtr() const { return opPtr; }

  std::string getOpName() const { return opName; }

private:
  double getCurrentTimeStamp();

  mlir::Operation * opPtr;
  std::string opName;
  double startTimestamp;
  double endTimestamp;
  double duration;
};
