#ifndef ML_PROFILER_TIMEMANAGER_H
#define ML_PROFILER_TIMEMANAGER_H

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "ml_profiler/TimeEvent.h"

// class Label {
// public:
//   Label(std::string n) : name(n) {}
//   std::string name;
// };

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

  void timingEnd(TimeEvent *e) { (*e).setEndTimestamp(); }

  // add timeEvent
  void addEvent(TimeEvent *event) { events.push_back(event); }

  TimeEvent *eventsBack() { return events.back(); }

  // process data
  void processTimingData(const std::string &outputFilepath);

private:
  // save all timeEvents
  std::vector<TimeEvent *> events;
};

#endif // ML_PROFILER_TIMEMANAGER_H