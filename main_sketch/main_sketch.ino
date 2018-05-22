#include <SoftwareSerial.h>
#include <Ultrasonic.h>
#include <Wire.h> 
#include "defs.h"
#include "bluetooth.h"
#include "debug.h"
#include "engine.h"
#include "shocker.h"
#include "servak.h"

#define DELAY_MS      200
#define CRITICAL_OBSTACLE_DISTANCE 40 /* centimeters */

Driver actions[] = {
    {'T', Engine::shutdown},
    {'F', Engine::driveForward},
    {'B', Engine::driveBackwards},
    {'I', Engine::speedUp},
    {'D', Engine::speedDown},
    {'L', Engine::turnLeft},
    {'R', Engine::turnRight},
    {'P', Servak::pushFire},
    {'S', Shocker::strike}
};

bool react(const char &command){
	for (const Driver & action: actions){
		if (action.key == command){
			action.respond();
			return true;
		}
	}
	return false;
}

static Ultrasonic rangefinder(4, 3); // trig, echo
static Bluetooth       blt(0, 1, 2); // RX, TX, STATE

void setup(){
  Debug::init();
  
  Engine::init(11, 12, 13,   // enA, in1, in2
                6,  8,  7);  // enB, in3, in4
  Servak::init(10);          // yellow wire
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
    blt.discardAllPendingData(); /* UNTESTED LINE */
    switch (ch) {
      case 'L':
      case 'R': break;
      case '+':{
        blt.discardAllPendingData(); /* received unnecessary bluetooth AT command */
        Engine::smoothSteering();
        return;
      }
      default: { Engine::smoothSteering(); }
    }
    Debug::log("Available: ", ch, ' ');
    react(ch);
  } else {
    Engine::smoothSteering();
  }
  processObstacleAvoiding();
  
  Debug::log("' SPEED LEFT: ", Engine::speedLeft, " SPEED RIGHT: ", Engine::speedRight);
  Debug::logln(" Current Thrust: ", Engine::thrust == Engine::Forward ? "forward" : Engine::thrust == Engine::Backward ? "backward" : "idle"); 
}









