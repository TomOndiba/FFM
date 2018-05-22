#include "bluetooth.h"

Bluetooth::Bluetooth(const pin_t & RX, const pin_t & TX, const pin_t & STATE, const int & baudrate)
  : serialPort(RX, TX), pin_state(STATE) 
{
  serialPort.begin(baudrate);
  pinMode(pin_state, INPUT);
}

  bool Bluetooth::isConnected() const{
    return digitalRead(pin_state);
  }

  int Bluetooth::dataAvailable() {
    return serialPort.available();
  }

  char Bluetooth::readChar(){
    return serialPort.read();
  }

  int Bluetooth::discardAllPendingData(){
    int discarded = dataAvailable();
    while (dataAvailable()){
      (void)readChar();
    }
    return discarded;
  }
  
