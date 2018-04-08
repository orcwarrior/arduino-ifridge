#ifndef FLOAT_EMIT_EVENT_HPP
#define FLOAT_EMIT_EVENT_HPP

#include <string>
#include "./Event.hpp"

class FloatEmitEvent : public Event
{
public:
  float val;
  FloatEmitEvent(float testVal) : Event("FloatEmitEvent")
  {
    this->val = testVal;
  };
};

#endif