#include "servak.h"

Servo Servak::serv;

void Servak::pushFire(){
  if (pushed){
    serv.write(0);
    pushed = false;
  } else {
    serv.write(SERV_ANGLE);
    pushed = true; 
    delay(100);
    Shocker::strike();
  }
}

bool Servak::pushed = false;

void Servak::init(const pin_t & pin){
  serv.attach(pin);
}
