#include "./dummy-libs/Arduino.h"
#include <stdio.h>
#include "./lib/EventManager/EventManager.hpp"

#define _SSD1306_LINUX_IO_H_ // so _SSD1306_LINUX_IO_H_ libs won't be parsed and throws errors

void setup(void);
void loop(void);
int main()
{
  const char* str = "Hi debugger, whatsapp?";
  setup();
  while(true) {loop();}
}