#ifndef SSD_DISPLAY_HPP
#define SSD_DISPLAY_HPP

#include "../lib/EventManager/Event/FloatEmitEvent.hpp"
#include <font6x8.h>
#include <nano_engine.h>
#include <ssd1306.h>
#include <limits>

class SSDDisplay
{
public:
  SSDDisplay()
  {
    this->initListeners();
    ssd1306_128x32_i2c_init();
    ssd1306_fillScreen(0x00);
    ssd1306_setFixedFont(ssd1306xled_font6x8);
    this->engine.begin();
  }
  void draw()
  {
    // ...
  }
  void updateSetTemp(Event *e)
  {
    FloatEmitEvent *setTempEvt = (FloatEmitEvent *)e;
    this->setTemperature       = setTempEvt->val;
    Serial.print("EventHandler: Change Set Temperature");
    Serial.println(setTempEvt->val);

    string setTemp;
    if (setTempEvt->val == NAN)
      setTemp = "OFF   ";
    else {
      setTemp = NumberToString<float>(setTempEvt->val, 1);
      setTemp += "'C  ";
    }
    ssd1306_clearBlock(2, 8, 40, 16);
    ssd1306_printFixed2x(2, 8, setTemp.c_str(), STYLE_NORMAL);
  }

private:
  void initListeners()
  {
    EventManager *man = EventManager::getInstance();
    man->addEventListener("changedSetTemperature",
                          BIND_MEM_CB(&SSDDisplay::updateSetTemp, this));
  }

  NanoEngine8 engine;
  // bool changesDone = true;
  float tempSensor     = NAN;
  float setTemperature = NAN;
};

#endif