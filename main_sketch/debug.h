#pragma once

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
