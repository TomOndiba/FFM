#pragma once
#include <SoftwareSerial.h>

unsigned char & increase(unsigned char & val, const unsigned char & step);
unsigned char & decrease(unsigned char & val, const unsigned char & step);

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
void approximateTo(TNumeric & countdown, const TNumeric & dest, const unsigned char & step = 1){
    if (countdown < dest){
      countdown += step;
    } else if (dest < countdown){
      countdown -= step;
    }
}


typedef void (*Executor)();

class Driver{
public:
	const char key;
	const Executor respond;
	Driver(const char & key, const Executor &response);
};



