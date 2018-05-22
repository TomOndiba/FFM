#include "defs.h"


unsigned char & increase(unsigned char & val, const unsigned char & step){
    if ((short)val + (short)step <= 255){
      val += step;
    } else {
      val = 255;
    }
    return val;
}

unsigned char & decrease(unsigned char & val, const unsigned char & step){
  if ((short)val - (short)step >= 0){
    val -= step;
  } else {
    val = 0;
  }
  return val;
}

Driver::Driver(const char &key, const Executor &response)
      : key(key), respond(response) {}
