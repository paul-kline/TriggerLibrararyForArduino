#include "Trigger.h"
#include "Arduino.h"


Trigger::Trigger(unsigned long timeInterval_, int threshold_, bool hightolow_, int initExtreme_){
 timeInterval = timeInterval_;
 threshold = threshold_;
 hightolow = hightolow_;
 extrememVal = initExtreme_;
 extremeRecTime = 0;
  
  
  
}
Trigger::Trigger()
{
  timeInterval = 100;
 threshold = -1;
 hightolow = true;
 extrememVal = -1;
 extremeRecTime = -1;
 

}
void Trigger::init(long unsigned int timeInterval_, int threshold_, bool hightolow_, int initExtreme_)
{
 timeInterval = timeInterval_;
 threshold = threshold_;
 hightolow = hightolow_;
 extrememVal = initExtreme_;
 extremeRecTime = 0; 
}



bool Trigger::shouldFire(int newMeasurement, unsigned long curTime){

 //now check if the current light level is more than threshold brighter.
    if(doesTrigger(newMeasurement)){
      maybeUpdate(newMeasurement, curTime); //still update. we only want one trigger. 
      //update(newMeasurement,curTime);
      return true;
    }
    
    
    
//     if(extremeRecTime < (curTime - timeInterval)){
//       extrememVal = newMeasurement;
//       extremeRecTime = curTime;
// 
//     }
    //at this point dimmestLight is guarenteed to be within the time interval.

    //if the curent light level is darker than the current dimmest, replace it.
    
    maybeUpdate(newMeasurement, curTime);
    //extrememVal = maybeReplace(newMeasurement); // new extremevalue if new extreme.
    
    
    //carry on wayward son.
    return false;
  
  
}


void Trigger::maybeUpdate(int newVal, unsigned long time){
  
  if(extremeRecTime < (time - timeInterval)){
      extrememVal = newVal;
      extremeRecTime = time;  
  }else{
    
   if(hightolow){
     if(extrememVal < newVal){
       update(newVal,time);
     }
    //else no changes.
   }else{
     if(extrememVal > newVal){
      update(newVal,time);
     }
   //else do nothing.
    }
  }
}
void Trigger::update(int newVal, unsigned long time){
 extrememVal = newVal;
 extremeRecTime = time;
} 
  
 
  
  


bool Trigger::doesTrigger(int val){
 if(hightolow){
   return (val < (extrememVal - threshold));
 }else{
   return (val > (extrememVal + threshold));
 }
}

int Trigger::getDiff(int newMeasurement)
{
  return (newMeasurement - extrememVal);

}

  