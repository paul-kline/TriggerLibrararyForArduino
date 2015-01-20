



//#include "Arduino.h"
#ifndef Trigger_h
#define Trigger_h


class Trigger
{
public:
  Trigger(unsigned long timeInterval_, int threshold_, bool hightolow_, int initExtreme_);  
  Trigger();
  void init(unsigned long timeInterval_, int threshold_, bool hightolow_, int initExtreme_);
  unsigned long timeInterval;
  int threshold;
  int extrememVal;
  
  bool hightolow;
  
  bool shouldFire(int newMeasurement, unsigned long curTime);
  
  int getDiff(int newMeasurement);
  
private:
  void maybeUpdate(int newVal, unsigned long time);
  void update(int newVal, unsigned long time);
  bool doesTrigger(int val);
  unsigned long extremeRecTime;
  
  
};
#endif