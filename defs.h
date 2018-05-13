#pragma once
#include <SoftwareSerial.h>
#include <Servo.h>

constexpr unsigned char SPEED_STEP = 51;
constexpr unsigned char START_ANGLE =  2;
constexpr unsigned char SERV_ANGLE = 30;
constexpr unsigned char TURN_SPEED_STEP = 51;

#define ANGLES {\
        15, \
   90 - 30, \
        90, \
   90 + 30, \
  180 - 15  \
  }


#define sizeat(arr) (sizeof(arr) / sizeof(arr[0]))
#define RETURN_IF(condition) do {if (condition) { return; } break; } while (false)
#define SET_OUTPUTS(...) \
  {\
  pin_t ____OUT__[] = {__VA_ARGS__};\
  setMode(____OUT__, sizeat(____OUT__), OUTPUT);\
  }

#define SET_INPUTS(...) \
  {\
  pin_t ____IN___[] = {__VA_ARGS__};\
  setMode(____IN___, sizeat(____IN___), INPUT);\
  }

typedef unsigned char pin_t;
typedef unsigned char mode_t;

void setMode(const pin_t * pins, unsigned char howMany, const mode_t &mode){
	while(howMany){
		pinMode(*pins++, mode);
		--howMany;
	}
}


template <typename TNumeric>
void approximateToZero(TNumeric & countdown, const unsigned char & step = 1){
    if (countdown < 0){
      countdown += step;
    } else if (countdown > 0){
      countdown -= step;
    }
}



namespace Debug{
	void init(const int & port = 9600);

  template<typename TLast>
  void logRecurrent(const TLast & lastArg){
    Serial.print(lastArg);
    // terminate recursion
  }

  template <typename TCurrent, typename... TRemainder>
  void logRecurrent(const TCurrent & current, const TRemainder &... remainder){
    Serial.print(current);
    logRecurrent(remainder...);
  }

  template <typename... TPrintable>
  void log(const TPrintable &... argv){
      logRecurrent(argv...);
  }

  template<typename TLast>
  void loglnRecurrent(const TLast & lastArg){
    Serial.println(lastArg);
    // terminate recursion
  }

  template <typename TCurrent, typename... TRemainder>
  void loglnRecurrent(const TCurrent & current, const TRemainder &... remainder){
    Serial.print(current);
    loglnRecurrent(remainder...);
  }

  template <typename... TPrintable>
  void logln(const TPrintable &... argv){
      loglnRecurrent(argv...);
  }
}

class Bluetooth {
private:
  SoftwareSerial serialPort;
  const pin_t pin_state;
public:
  Bluetooth(const pin_t & RX, const pin_t & TX, const pin_t & STATE, const int & baudrate = 9600);
  
  bool isConnected() const;
  int dataAvailable();
  char readChar();
};

typedef void (*Executor)();

class Driver{
public:
	const char key;
	const Executor respond;
	Driver(const char & key, const Executor &response);
};

class Shocker: public Driver {
private:
  static pin_t pin;
public:
   static void init(const pin_t & pin);
   static void strike();
};

class Servak: public Driver{
  static Servo serv;
  static bool pushed;
public:
  Servak(const char & key, const Executor &response) : Driver(key, response) {}
  static void init(const pin_t & pin);
  static void push();
};


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

