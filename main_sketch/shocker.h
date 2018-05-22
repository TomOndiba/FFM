#pragma once
#include "defs.h"
class Shocker: public Driver {
private:
  static pin_t pin;
public:
   static void init(const pin_t & pin);
   static void strike();
};

