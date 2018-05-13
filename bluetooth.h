#pragma once

class Bluetooth {
private:
  SoftwareSerial serialPort;
  const pin_t pin_state;
public:
  Bluetooth(const pin_t & RX, const pin_t & TX, const pin_t & STATE, const int & baudrate = 9600);
  
  bool isConnected() const;
  int dataAvailable();
  char readChar();
  int discardAllPendingData(); /* returns amount of characters discarded */

  template <typename T>
  void write(const T & message){
    serialPort.write(message);
  }
};
