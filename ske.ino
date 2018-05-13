#include <SoftwareSerial.h>
#include "defs.h"
#include <Ultrasonic.h>
#include <Wire.h> 

#define DELAY_MS      200
#define CRITICAL_OBSTACLE_DISTANCE 10 /* centimeters */

Driver actions[] = {
    {'T', Engine::shutdown},
    {'F', Engine::driveForward},
    {'B', Engine::driveBackwards},
    {'I', Engine::speedUp},
    {'D', Engine::speedDown},
    {'L', Engine::turnLeft},
    {'R', Engine::turnRight},
    {'P', Servak::push},
    {'S', Shocker::strike}
};

bool react(const char &command){
	for (unsigned char i = 0; i < sizeat(actions); ++i){
		if (actions[i].key == command){
			actions[i].respond();
			return true;
		}
	}
	return false;
}

static Ultrasonic rangefinder(4, 3);
static Bluetooth blt(0, 1, 2); // RX, TX, STATE

void setup(){
  Debug::init();
  
  Engine::init(11, 12, 13,   // enA, in1, in2
               6,  8, 7);  // enB, in3, in4
  Servak::init(10);
  Shocker::init(5);
}

void processObstacleAvoiding(){
  RETURN_IF(Engine::isIdle() || Engine::thrust == Engine::Thrust::Forward);
  int range = rangefinder.Ranging(CM);
  Debug::logln("RANGE: ", range);
  if (range <= CRITICAL_OBSTACLE_DISTANCE){
    Engine::shutdown();
  }
}

void loop(){
  delay(DELAY_MS);
    
  if (!blt.isConnected()){
    Engine::shutdown();
    return;
  }
  if (blt.dataAvailable()){
    char ch = blt.readChar();
    switch (ch) {
      case 'L':
      case 'R': break;
      default: { Engine::smoothSteering(); }
    }
    react(ch);
  } else {
    Engine::smoothSteering();
  }
  processObstacleAvoiding();
  
  Debug::log("' SPEED LEFT: ", Engine::speedLeft, " SPEED RIGHT: ", Engine::speedRight);
  Debug::logln(" Current Thrust: ", Engine::thrust == Engine::Forward ? "forward" : Engine::thrust == Engine::Backward ? "backward" : "idle"); 
}








