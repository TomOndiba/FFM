#pragma once

#include <Servo.h>
#include "defs.h"

const constexpr unsigned char SERV_ANGLE = 30; /* degrees to push */

class Servak: public Driver{
  static Servo serv;
  static bool pushed;
public:
  Servak(const char & key, const Executor &response) : Driver(key, response) {}
  static void init(const pin_t & pin);
  static void pushFire();
};
