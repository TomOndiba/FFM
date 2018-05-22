#include "defs.h"

namespace Debug {
	void init(const int &port) {
		Serial.begin(port); 
	}
}

