#ifndef FRIDGE_CONTROLLER_HPP
#define FRIDGE_CONTROLLER_HPP

#include "./SSDDisplay.hpp"
#include "./TemperatureSensor.hpp"
#include <limits>

class FridgeController
{
public:
  FridgeController()
  {
    this->display = new SSDDisplay();
    this->sensor = new TemperatureSensor();
    this->initListeners();
  }

private:
  EventManager *evtMan = EventManager::getInstance();
  void initListeners()
  {
    evtMan->addEventListener("ReadPin-0",
                             BIND_MEM_CB(&FridgeController::updateSetTemp, this));
  }
  void updateSetTemp(Event *e)
  {
    ReadPinEvent *sensorEvt = (ReadPinEvent *)e;
    this->setTemperatureRaw = sensorEvt->val;
    float setTemp           = this->calculateSetTemperature();
    if (setTemp != this->setTemperature) {
      this->setTemperature = setTemp;
      Serial.println("Dispatch: Change Set Temperature");
      evtMan->dispatchEvent("changedSetTemperature",
                            new FloatEmitEvent(setTemp));
    }
    // TODO Handle temp and sensor to change freezing/etc.(new class?)
  }
  float calculateSetTemperature()
  {
    if (this->setTemperatureRaw == 0) return NAN; // Potentiometer is in OFF (less than 5) state
    const float tempRange[] = {12, -1 };
    const int range         = tempRange[0] - tempRange[1];
    const float fract       = this->setTemperatureRaw / 1023.0;
    return floatApprox(tempRange[0] - (range * fract), 1);
  }

  SSDDisplay *display;
  TemperatureSensor *sensor;
  float tempSensorValue = NAN;
  float setTemperature  = 6.0; // "Default" temp (when readPin has some issues)
  int setTemperatureRaw = 512;
};

#endif