#ifndef ANALOG_PIN_READER_HPP
#define ANALOG_PIN_READER_HPP

#include "../lib/EventManager/Event/Event.hpp"
#include "../lib/EventManager/EventManager.hpp"
#include "../lib/IntervalManager/Interval.hpp"
#include "../lib/IntervalManager/IntervalManager.hpp"
#include "../lib/utils.hpp"
#include <string>
#include <limits>
#include <sstream>

using namespace std;



class ReadPinEvent : public Event
{
public:
  ReadPinEvent(int value)
  : Event("ReadPinEvent")
  {
    this->val =  value;
  }
  int val;
};

class AnalogPinReader
{
private:
  int pin;
  Interval *readInterval;
  int lastVal = NAN;
  std::string eventName;

public:
  AnalogPinReader(int pin)
  {
  pinMode(pin, INPUT);
    this->pin          = pin;
    this->readInterval = new Interval(BIND_MEM_CB(&AnalogPinReader::readOnInterval, this), 100);
    this->eventName = this->getMyEventName(this->pin);
    IntervalManager::getInstance()->add(this->readInterval);
    // TODO: Remove interval on destroy?
    // DK: I hate magic numbers, but c++ hates elegant way to declare const etc. :/
  };

  std::string getMyEventName(int pin)
  {
    return "ReadPin-" + NumberToString<int>(pin);
  }

  int read()
  {
    const int IGNORED_DELTA = 2;
    int v = analogRead(this->pin);
    // string msg = "AnalogRead: "; msg  += NumberToString<int>(v);
    // Serial.println(msg.c_str());

    if (this->lastVal == NAN || (v - IGNORED_DELTA > this->lastVal) ||
        (v + IGNORED_DELTA < this->lastVal)) {
      this->lastVal        = v;
      EventManager::getInstance()->dispatchEvent(this->eventName, new ReadPinEvent(v));
      return v;
    }
  }
  void readOnInterval(Interval* i) {
    read();
  }
};

#endif