#include "defs.h"

namespace Debug {
	void init(const int &port) {
		Serial.begin(port); 
	}

  
	void log(const char * const &message) {
		Serial.print(message);
	}

	void log(const char &ch) {
		Serial.print(ch);
	}

  void log(const int &i){
    Serial.print(i, DEC);
  }

  void logln(const char * const & message){
    Serial.println(message);
  }
  void logln(const char & ch){
    Serial.println(ch);
  }
  void logln(const int& i){
    Serial.println(i, DEC);
  }

}

