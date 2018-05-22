#include "defs.h"

Engine::Engine(const char & key, const Executor &response)
		: Driver(key, response) {}

unsigned char Engine::speedLeft   = 0;
unsigned char Engine::speedRight  = 0;

pin_t Engine::pin_velocityLeft    = 0;
pin_t Engine::pin_engineForwLeft  = 0;
pin_t Engine::pin_engineBackLeft  = 0;

pin_t Engine::pin_velocityRight   = 0;
pin_t Engine::pin_engineForwRight = 0;
pin_t Engine::pin_engineBackRight = 0;

Engine::Thrust Engine::thrust = Engine::Thrust::Forward;

void Engine::init(const pin_t & enA, 
                  const pin_t & in1,
                  const pin_t & in2,
                  
                  const pin_t & enB, 
                  const pin_t & in3,
                  const pin_t & in4){
                    
  pin_velocityLeft   = enA;
  pin_engineBackLeft = in1;
  pin_engineForwLeft = in2;
  //
  pin_velocityRight   = enB;
  pin_engineBackRight = in3;
  pin_engineForwRight = in4;
  
  pinMode(pin_velocityLeft,    OUTPUT);
  pinMode(pin_engineBackLeft,  OUTPUT);
  pinMode(pin_engineForwLeft,  OUTPUT);
 
  pinMode(pin_velocityRight,   OUTPUT);
  pinMode(pin_engineBackRight, OUTPUT);
  pinMode(pin_engineForwRight, OUTPUT);

  speedRight = speedLeft = 0;
	analogWrite(pin_velocityLeft,  0);
  analogWrite(pin_velocityRight, 0);
}

void Engine::speedDown(){ Engine::speedDown(SPEED_STEP); }
void Engine::speedUp(){   Engine::speedUp  (SPEED_STEP); }


void Engine::speedDown(const unsigned char & step){
	setLeftSpeed(decrease(speedLeft,  step));
  setRightSpeed(decrease(speedRight, step));
}

void Engine::speedUp(const unsigned char & step){
  bool wasIdle { isIdle() };
	setLeftSpeed(increase(speedLeft,  step));
  setRightSpeed(increase(speedRight, step));
  if (wasIdle){
    switch (thrust){
      case Forward:{  driveForward();   return;}
      case Backward:{ driveBackwards(); return; }
    }
  }
}

void Engine::sleep(){
    analogWrite(pin_velocityLeft, 0);
    analogWrite(pin_velocityRight, 0);
}

void Engine::wakeUp(){
  analogWrite(pin_velocityLeft, speedLeft);
  analogWrite(pin_velocityRight, speedRight);
}

void Engine::driveForward(){
  bool sleeped = false;
  if (thrust == Backward){
    sleep();
    delay(200);
    sleeped = true;
  }
  thrust = Forward;
	digitalWrite(pin_engineBackLeft,  LOW);
	digitalWrite(pin_engineForwLeft,  HIGH);
 
  digitalWrite(pin_engineBackRight, LOW);
  digitalWrite(pin_engineForwRight, HIGH);
  if (sleeped){
    wakeUp();
  }
  alignWheels();
}

void Engine::driveBackwards(){
  bool sleeped = false;
  if (thrust == Forward){
    sleep();
    delay(200);
    sleeped = true;
  }
  thrust = Backward;
  digitalWrite(pin_engineBackLeft,  HIGH);
  digitalWrite(pin_engineForwLeft,  LOW);

  digitalWrite(pin_engineBackRight, HIGH);
  digitalWrite(pin_engineForwRight, LOW);
  if (sleeped){
    wakeUp();
  }
  alignWheels();
}

Engine::LessSpeedOn Engine::lessSpeed(){
  if (speedLeft < speedRight){
     return LessSpeedOn::LeftEngine;
  } else if (speedRight < speedLeft) {
     return LessSpeedOn::RightEngine;
  } else {
    return LessSpeedOn::Aligned;
  }
}

void Engine::alignWheels(){
  switch (lessSpeed()){
    case LessSpeedOn::LeftEngine:{  setLeftSpeed(speedRight);   return; }
    case LessSpeedOn::RightEngine:{ setRightSpeed(speedLeft); return; }
    case LessSpeedOn::Aligned:{ return; }
    default: { Debug::logln("SIGSEGV: illegal return value for alignLogicalSpeed()"); }
  }
}

void Engine::shutdown(){
  setLeftSpeed(0);
  setRightSpeed(0);
	digitalWrite(pin_engineBackLeft,  LOW);
	digitalWrite(pin_engineForwLeft,  LOW);

  digitalWrite(pin_engineBackRight, LOW);
  digitalWrite(pin_engineForwRight, LOW);
}

void Engine::smoothSteering(const unsigned char & step){
  switch (lessSpeed()){
    case LeftEngine:{
      setLeftSpeed(speedLeft + step < speedRight ? speedLeft + step : speedRight);
      return;
    }
    case RightEngine: {
      setRightSpeed(speedRight + step < speedLeft ? speedRight + step : speedLeft);
      return;
    }
    default: return;
  }
}

void Engine::turnLeft() { Engine::turnLeft (TURN_SPEED_STEP); }
void Engine::turnRight(){ Engine::turnRight(TURN_SPEED_STEP); }

void Engine::turnLeft(const unsigned char & step){
  if (speedLeft > speedRight) {
     setRightSpeed(increase(speedRight, step));
  } else {
     setLeftSpeed(decrease(speedLeft, step));      
  }
}
void Engine::turnRight(const unsigned char & step){
  if(speedRight > speedLeft){
    setLeftSpeed(increase(speedLeft,  step));
  }  else {
    setRightSpeed(decrease(speedRight, step));  
  }
}

void Engine::setLeftSpeed(const unsigned char & speed){
  analogWrite(pin_velocityLeft, (speedLeft = speed));
}

void Engine::setRightSpeed(const unsigned char & speed){
  analogWrite(pin_velocityRight, (speedRight = speed));
}

bool Engine::isIdle(){
  return speedLeft == 0 && speedRight == 0;
}

bool Engine::wheelsAreAligned(){
  return speedLeft == speedRight;
}



