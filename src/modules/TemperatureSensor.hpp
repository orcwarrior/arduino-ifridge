#ifndef TEMPERATURE_SENSOR_HPP
#define TEMPERATURE_SENSOR_HPP

#include "../lib/EventManager/Event/FloatEmitEvent.hpp"
#include "../lib/EventManager/EventManager.hpp"
#include "../lib/IntervalManager/Interval.hpp"
#include "../lib/IntervalManager/IntervalManager.hpp"
#include <string>
#include <AM2320.h>
#include <limits>

using namespace std;

class TemperatureSensor
{
private:
  Interval *readInterval;
  float lastTemp     = NAN;
  float lastHumidity = NAN;
  AM2320 *sensor;

public:
  TemperatureSensor(int powerPin = NULL)
  {
     pinMode(powerPin, OUTPUT);
    digitalWrite(powerPin, HIGH); // Temperature sensor can be connected to
                                  // digital pin to power it up
    this->readInterval = new Interval(BIND_MEM_CB(&TemperatureSensor::readOnInterval, this), 1000);
    this->sensor = new AM2320();
    IntervalManager::getInstance()->add(this->readInterval);
    // TODO: Remove interval on destroy?
  };

  int read()
  {
    int ths = this->sensor->Read();
    switch (ths) {
      case 2:
        this->handleError();
        Serial.println("TS:CRC failed");
        break;
      case 1:
        Serial.println("TS:Sensor offline");
        break;
      case 0:
      if (this->lastTemp == NAN || this->lastTemp != this->sensor->t) {
        this->lastTemp = this->sensor->t;
        EventManager::getInstance()->dispatchEvent("Sensor:Temperature", new FloatEmitEvent(this->lastTemp));
        }
      if (this->lastHumidity == NAN || this->lastHumidity != this->sensor->h) {
        this->lastHumidity = this->sensor->h;
        EventManager::getInstance()->dispatchEvent("Sensor:Humidity", new FloatEmitEvent(this->lastHumidity));
        }
    }
  }
  void readOnInterval(Interval *i) { read(); }
  void handleError() {
    // right now, do nothing
  }
};

#endif