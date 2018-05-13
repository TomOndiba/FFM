#include "shocker.h"

pin_t Shocker::pin = 0;

void Shocker::init(const pin_t & pin){
  pinMode(pin, OUTPUT);
  Shocker::pin = pin;
}

void Shocker::strike(){
  digitalWrite(pin, HIGH);
  delay(200);
  digitalWrite(pin, LOW);
}
