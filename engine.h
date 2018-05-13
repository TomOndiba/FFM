#pragma once

#include "defs.h"

constexpr unsigned char SPEED_STEP = 51;
constexpr unsigned char TURN_SPEED_STEP = 51;

class Engine: public Driver{
public:

  enum Thrust {
    Forward,
    Backward
  };

  static Thrust thrust;

  static unsigned char speedLeft;
  static unsigned char speedRight;
  
  static pin_t pin_velocityLeft;
  static pin_t pin_engineForwLeft;
  static pin_t pin_engineBackLeft;
  
  static pin_t pin_velocityRight;
  static pin_t pin_engineForwRight;
  static pin_t pin_engineBackRight;
  
public:
  Engine() = delete;
  Engine(const char & key, const Executor &response);

  static void init(const pin_t & enA, 
                   const pin_t & in1,
                   const pin_t & in2,
                   
                   const pin_t & enB, 
                   const pin_t & in3,
                   const pin_t & in4);

  static void speedDown(const unsigned char & step);
  static void speedUp(const unsigned char & step);
  static void speedDown();
  static void speedUp();

  static void driveForward();
  static void driveBackwards();

  static void turnLeft(const unsigned char & step);
  static void turnRight(const unsigned char & step);
  static void turnLeft();
  static void turnRight();
  static void shutdown();
  static void alignWheels();
  static bool isIdle();
  static bool wheelsAreAligned();
  static void sleep();
  static void wakeUp();

  static void setLeftSpeed(const unsigned char & speed);
  static void setRightSpeed(const unsigned char & speed);
  static void smoothSteering(const unsigned char & step = 25);
  
private:  
  enum LessSpeedOn { LeftEngine, RightEngine, Aligned };
  static LessSpeedOn lessSpeed();
};
