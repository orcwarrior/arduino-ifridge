#ifndef POT_HPP
#define POT_HPP

#include <string>
#include "../lib/IntervalManager/Interval.hpp"

const int DEFAULT_READ_INTERVAL_MS = 100;
const int IGNORED_DELTA = 3;

class AnalogPinReader
{
public:
  int pin;
  Interval* readInterval;
  int lastVal = -1;
  string eventName;

public:
  AnalogPinReader(int pin)
  {
    this->pin = pin;
    this->eventName = getMyEventName(pin);
    this->readInterval = new Interval(BIND_MEM_CB(&AnalogPinReader::read, this));
  };

  string getMyEventName(pin) { return "AnalogReadPin-" + std::to_string(pin); }

  int read() {
    int v =  analogRead(this->pin);
    if (this->lastVal == -1
    || (v - IGNORED_DELTA > this->lastVal)
    || (v + IGNORED_DELTA < this->lastVal)) {
     
     this->lastVal = v; 
    }

  }
};

#endif