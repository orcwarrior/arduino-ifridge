#include "./lib/callback.hpp"

#if defined(PLATFORM_IO)
#include "./main.platform.h"
#else
#include "./main.debug.h"
#endif

#include "./lib/IntervalManager/IntervalManager.hpp"
#include "./lib/utils.hpp"
#include "./modules/AnalogPinReader.hpp"
#include <iostream>
#include <stdio.h>

using util::Callback;

IntervalManager *intervalMan = IntervalManager::getInstance();
EventManager *man            = EventManager::getInstance();

bool ledState = false;
void ledToggle(Interval *i)
{
  ledState = !ledState;
  digitalWrite(LED_BUILTIN, ledState);
  // string msg = "LED Toggle: ";
  // msg += NumberToString<int>(i->getInterval());
  // Serial.println(msg.c_str());
}
Interval *ledToggleInterval = new Interval(BIND_FREE_CB(ledToggle), 2);

void onPotChange(Event *e)
{
  ReadPinEvent *read = (ReadPinEvent *)e;
  // string msg         = "onPotChange: ";
  // msg += NumberToString<int>(read->value / 2);
  // Serial.println(msg.c_str());

  ledToggleInterval->setInterval(read->value / 2);
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Test");

  pinMode(LED_BUILTIN, OUTPUT);
  intervalMan->add(ledToggleInterval);
  AnalogPinReader *potA0 = new AnalogPinReader(0);
  man->addEventListener("ReadPin-0", BIND_FREE_CB(onPotChange));
}

int loops = 0;
void loop()
{
  intervalMan->run();
  // if ((++loops % 1500) == 0) {
  //   string msg = "LT: ";
  //   msg += NumberToString<int>(t2 - t1);
  //   Serial.println(msg.c_str());
  // }
}